/*!
  @file src/adders/add_inertia_moment.cpp
  @brief This file has an implementation of the AddInertiaMoment class,
  which is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/15
  @details For more details, please see the header file,
  src/adders/add_inertia_moment.h.
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

void AddInertiaMoment::compute_with_weights(
  Json &data,
  const ElPtr &el_atoms)
{
  auto id2index_atom = ut::map_to_index(el_atoms->get_data(), "id");

  ArrayXd ms_atom;
  el_atoms->array1d(ms_atom, "mass");

  ArrayXXd rs_atom;
  el_atoms->array2d(rs_atom, {"xu", "yu", "zu"});

  for (auto &d : data)
  {
    RowArrayXd r_mol(3);
    r_mol << d["xu"], d["yu"], d["zu"];

    Matrix3d sum = Matrix3d::Zero();

    auto &atom_ids = d["atom-ids"];
    auto &atom_weights = d["atom-weights"];

    auto n_atoms = atom_ids.size();

    for (int i = 0; i != n_atoms; ++i)
    {
      auto id = atom_ids[i].get<int>();
      auto weight = atom_weights[i].get<double>();

      auto index = id2index_atom[id];
      auto mass = ms_atom(index) * weight;

      RowVector3d dr = rs_atom.row(index) - r_mol;

      sum += mass * dr.transpose() * dr;
    }

    auto tr = sum.trace();

    d["I_xx"] = tr - sum(0, 0);
    d["I_yy"] = tr - sum(1, 1);
    d["I_zz"] = tr - sum(2, 2);
    d["I_xy"] = -sum(0, 1);
    d["I_xz"] = -sum(0, 2);
    d["I_yz"] = -sum(1, 2);

  }
}

/* ------------------------------------------------------------------ */

void AddInertiaMoment::compute_without_weights(
  Json &data,
  const ElPtr &el_atoms)
{
  auto id2index_atom = ut::map_to_index(el_atoms->get_data(), "id");

  ArrayXd ms_atom;
  el_atoms->array1d(ms_atom, "mass");

  ArrayXXd rs_atom;
  el_atoms->array2d(rs_atom, {"xu", "yu", "zu"});

  for (auto &d : data)
  {
    RowArrayXd r_mol(3);
    r_mol << d["xu"], d["yu"], d["zu"];

    Matrix3d sum = Matrix3d::Zero();

    for (const int id : d["atom-ids"])
    {
      auto index = id2index_atom[id];
      auto mass = ms_atom(index);

      RowVector3d dr = rs_atom.row(index) - r_mol;

      sum += mass * dr.transpose() * dr;
    }

    auto tr = sum.trace();

    d["I_xx"] = tr - sum(0, 0);
    d["I_yy"] = tr - sum(1, 1);
    d["I_zz"] = tr - sum(2, 2);
    d["I_xy"] = -sum(0, 1);
    d["I_xz"] = -sum(0, 2);
    d["I_yz"] = -sum(1, 2);
  }
}

/* ------------------------------------------------------------------ */

void AddInertiaMoment::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  datakeys.required({"atom-ids", "xu", "yu", "zu"});

  auto el_atoms = ext_generator->get_element();

  el_atoms->required({"id", "mass", "xu", "yu", "zu"});

  if (datakeys.optional("atom-weights"))
  {
    compute_with_weights(data, el_atoms);
  }
  else
  {
    compute_without_weights(data, el_atoms);
  }

  datakeys.add({"I_xx", "I_yy", "I_zz", "I_xy", "I_xz", "I_yz"});
}

/* ------------------------------------------------------------------ */
