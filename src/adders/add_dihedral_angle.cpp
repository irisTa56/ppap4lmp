/*!
  @file src/adders/add_dihedral_angle.cpp
  @brief This file has an implementation of AddDihedralAngle class,
  which is a subclass of Adder class.
  @author Yang Juntao
  @date 2018/12/24
*/

#include "add_dihedral_angle.h"
#include "../utils/map_to_index.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddDihedralAngle::AddDihedralAngle(
  const ElPtr &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddDihedralAngle::compute_impl(
  Json &data)
{
  check_required_keys({"atom1-id", "atom2-id","atom3-id", "atom4-id"});

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
    RowVector3d r4 = rs_atom.row(id2index_atom[d["atom4-id"]]);

    auto vec_1to2 = r2 - r1;
    auto vec_2to3 = r3 - r2;
    auto vec_3to4 = r4 - r3;

    auto n123 = vec_1to2.cross(vec_2to3);
    auto n234 = vec_2to3.cross(vec_3to4);

    d["dihedral-angle"] = rad2deg * acos(
      n123.dot(n234) / (n123.norm() * n234.norm()));
  }
}

/* ------------------------------------------------------------------ */
