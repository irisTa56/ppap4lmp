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
  Json &data,
  DataKeys &datakeys)
{
  datakeys.required({"atom1-id", "atom2-id","atom3-id", "atom4-id"});

  auto el_atoms = ext_generator->get_element();

  el_atoms->required({"id", "xu", "yu", "zu"});

  auto &atoms = el_atoms->get_data();

  auto id2index_atom = ut::map_to_index(atoms, "id");

  for (auto &d : data)
  {
    auto index1 = id2index_atom[d["atom1-id"]];
    auto index2 = id2index_atom[d["atom2-id"]];
    auto index3 = id2index_atom[d["atom3-id"]];
    auto index4 = id2index_atom[d["atom4-id"]];
    auto &atom1 = atoms[index1];
    auto &atom2 = atoms[index2];
    auto &atom3 = atoms[index3];
    auto &atom4 = atoms[index4];
    double xu1 = atom1["xu"];
    double yu1 = atom1["yu"];
    double zu1 = atom1["zu"];
    double xu2 = atom2["xu"];
    double yu2 = atom2["yu"];
    double zu2 = atom2["zu"];
    double xu3 = atom3["xu"];
    double yu3 = atom3["yu"];
    double zu3 = atom3["zu"];
    double xu4 = atom4["xu"];
    double yu4 = atom4["yu"];
    double zu4 = atom4["zu"];

    double vec1[3] = {xu1-xu2 , yu1-yu2 , zu1-zu2};
    double vec2[3] = {xu2-xu3 , yu2-yu3 , zu2-zu3};
    double vec3[3] = {xu3-xu4 , yu3-yu4 , zu3-zu4};

    double b12[3] =  {
    (vec1[1]*vec2[2]-vec2[1]*vec1[2]),
    (vec2[0]*vec1[2]-vec1[0]*vec2[2]),
    (vec1[0]*vec2[1]-vec2[0]*vec1[1])
    };

    double b23[3] = {
    (vec2[1]*vec3[2]-vec3[1]*vec2[2]),
    (vec3[0]*vec2[2]-vec2[0]*vec3[2]),
    (vec2[0]*vec3[1]-vec3[0]*vec2[1])
    };

    double b123[3] = {
    (b12[1]*b23[2]-b23[1]*b12[2]),
    (b23[0]*b12[2]-b12[0]*b23[2]),
    (b12[0]*b23[1]-b23[0]*b12[1])
    };

    double b2u[3] = {
    (vec2[0]/sqrt(vec2[0]*vec2[0]+vec2[1]*vec2[1]+vec2[2]*vec2[2])),
    (vec2[1]/sqrt(vec2[0]*vec2[0]+vec2[1]*vec2[1]+vec2[2]*vec2[2])),
    (vec2[2]/sqrt(vec2[0]*vec2[0]+vec2[1]*vec2[1]+vec2[2]*vec2[2]))
    };

    double y = b123[0]*b2u[0]+b123[1]*b2u[1]+b123[2]*b2u[2];
    double x = b12[0]*b23[0]+b12[1]*b23[1]+b12[2]*b23[2];

    d["dihedral_angle"] = abs(atan2(y,x));
  }

  datakeys.add("dihedral_angle");
}

/* ------------------------------------------------------------------ */
