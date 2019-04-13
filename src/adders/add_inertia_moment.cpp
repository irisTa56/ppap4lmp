/*!
  @file src/adders/add_inertia_moment.cpp
  @brief This file has an implementation of the AddInertiaMoment class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

#include "add_inertia_moment.h"
#include "../utils/map_to_index.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddInertiaMoment::AddInertiaMoment(
  const ElPtr &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddInertiaMoment::compute_impl(
  Json &data,
  JsonToVoidFunc check_required_keys,
  JsonToBoolFunc check_optional_keys)
{
  check_required_keys({"atom-ids", "xu", "yu", "zu"});

  auto el_atoms = ext_generator->get_element();

  el_atoms->check_required_keys({"id", "mass", "xu", "yu", "zu"});

  auto id2index_atom = ut::map_to_index(el_atoms->get_data(), "id");

  ArrayXd ms_atom;
  el_atoms->make_1darray_from_data(ms_atom, "mass");

  ArrayXXd rs_atom;
  el_atoms->make_2darray_from_data(rs_atom, {"xu", "yu", "zu"});

  for (auto &d : data)
  {
    RowArrayXd r_mol(3);
    r_mol << d["xu"], d["yu"], d["zu"];

    Matrix3d inertia_tensor = Matrix3d::Zero();

    auto &atom_ids = d["atom-ids"];

    auto atom_weights = d.value(
      "atom-weights", Vec<double>(atom_ids.size(), 1.0));

    auto n_atoms = atom_ids.size();

    for (int i = 0; i != n_atoms; ++i)
    {
      auto id = atom_ids[i];
      auto weight = atom_weights[i];

      auto index = id2index_atom[id];
      auto mass = ms_atom(index) * weight;

      RowVector3d dr = rs_atom.row(index) - r_mol;

      inertia_tensor += mass * dr.transpose() * dr;
    }

    auto tr = inertia_tensor.trace();

    d["I_xx"] = tr - inertia_tensor(0, 0);
    d["I_yy"] = tr - inertia_tensor(1, 1);
    d["I_zz"] = tr - inertia_tensor(2, 2);
    d["I_xy"] = -inertia_tensor(0, 1);
    d["I_xz"] = -inertia_tensor(0, 2);
    d["I_yz"] = -inertia_tensor(1, 2);
  }
}
