/*!
  @file src/adders/add_bond_angle.cpp
  @brief This file has an implementation of AddBondAngle class,
  which is a subclass of Adder class.
  @author Yang Juntao
  @date 2018/12/20
*/

#include <cmath>

#include "add_bond_angle.h"
#include "../utils/map_to_index.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddBondAngle::AddBondAngle(
  const ElPtr &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddBondAngle::compute_impl(
  Json &data)
{
  check_required_keys({"atom1-id", "atom2-id", "atom3-id"});

  auto el_atoms = ext_generator->get_element();

  el_atoms->check_required_keys({"id", "xu", "yu", "zu"});

  auto id2index_atom = ut::map_to_index(el_atoms->get_data(), "id");

  ArrayXXd rs_atom;
  el_atoms->make_2darray_from_data(rs_atom, {"xu", "yu", "zu"});

  const double rad2deg = 180.0 / M_PI;

  for (auto &d : data)
  {
    RowVector3d r1 = rs_atom.row(id2index_atom[d["atom1-id"]]);
    RowVector3d r2 = rs_atom.row(id2index_atom[d["atom2-id"]]);
    RowVector3d r3 = rs_atom.row(id2index_atom[d["atom3-id"]]);

    auto vec1 = r1 - r2;
    auto vec2 = r3 - r2;

    d["angle"] = rad2deg * acos(
      vec1.dot(vec2) / (vec1.norm() * vec2.norm()));
  }
}

/* ------------------------------------------------------------------ */
