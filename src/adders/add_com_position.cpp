/*!
  @file src/adders/add_com_position.cpp
  @brief This file has an implementation of AddCoMPosition class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/13
*/

#include "add_com_position.h"
#include "../utils/map_to_index.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddCoMPosition::AddCoMPosition(
  const ElPtr &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddCoMPosition::compute_impl(
  Json &data,
  JsonToVoidFunc check_required_keys,
  JsonToBoolFunc check_optional_keys)
{
  check_required_keys("atom-ids");

  auto el_atoms = ext_generator->get_element();

  el_atoms->check_required_keys({"id", "mass", "xu", "yu", "zu"});

  auto id2index_atom = ut::map_to_index(el_atoms->get_data(), "id");

  ArrayXd ms_atom;
  el_atoms->make_1darray_from_data(ms_atom, "mass");

  ArrayXXd rs_atom;
  el_atoms->make_2darray_from_data(rs_atom, {"xu", "yu", "zu"});

  for (auto &d : data)
  {
    double sum_mass = 0.0;
    RowArrayXd tmp_r = RowArrayXd::Zero(3);

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

      sum_mass += mass;
      tmp_r += mass * rs_atom.row(index);
    }

    tmp_r /= sum_mass;

    d["mass"] = sum_mass;

    d["xu"] = tmp_r(0);
    d["yu"] = tmp_r(1);
    d["zu"] = tmp_r(2);
  }
}
