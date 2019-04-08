/*!
  @file src/adders/add_bond_length.cpp
  @brief This file has an implementation of AddBondLength class,
  which is a subclass of Adder class.
  @author Yang Juntao & Kawai Kento
  @date 2018/12/06
*/

#include "add_bond_length.h"
#include "../utils/map_to_index.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddBondLength::AddBondLength(
  const ElPtr &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddBondLength::compute_impl(
  Json &data)
{
  check_required_keys({"atom1-id", "atom2-id"});

  auto el_atoms = ext_generator->get_element();

  el_atoms->check_required_keys({"id", "xu", "yu", "zu"});

  auto id2index_atom = ut::map_to_index(el_atoms->get_data(), "id");

  ArrayXXd rs_atom;
  el_atoms->make_2darray_from_data(rs_atom, {"xu", "yu", "zu"});

  for (auto &d : data)
  {
    d["length"] = RowVector3d(
      rs_atom.row(id2index_atom[d["atom2-id"]])
      - rs_atom.row(id2index_atom[d["atom1-id"]])).norm();
  }
}

/* ------------------------------------------------------------------ */
