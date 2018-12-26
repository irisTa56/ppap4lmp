/*!
  @file src/adders/add_angle.cpp
  @brief This file has an implementation of AddAngle class,
  which is a subclass of Adder class.
  @author Yang Juntao
  @date 2018/12/20
*/

#include "add_angle.h"
#include "../utils/map_to_index.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddAngle::AddAngle(
  const ElPtr &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddAngle::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  datakeys.required({"atom1-id", "atom2-id", "atom3-id"});

  auto el_atoms = ext_generator->get_element();

  el_atoms->required({"id", "xu", "yu", "zu"});

  auto &atoms = el_atoms->get_data();

  auto id2index_atom = ut::map_to_index(atoms, "id");

  for (auto &d : data)
  {
    auto index1 = id2index_atom[d["atom1-id"]];
    auto index2 = id2index_atom[d["atom2-id"]];
    auto index3 = id2index_atom[d["atom3-id"]];
    auto &atom1 = atoms[index1];
    auto &atom2 = atoms[index2];
    auto &atom3 = atoms[index3];
    double xu1 = atom1["xu"];
    double xu2 = atom2["xu"];
    double xu3 = atom3["xu"];
    double yu1 = atom1["yu"];
    double yu2 = atom2["yu"];
    double yu3 = atom3["yu"];
    double zu1 = atom1["zu"];
    double zu2 = atom2["zu"];
    double zu3 = atom3["zu"];
    double vec1[3] = {xu1-xu2 , yu1-yu2 , zu1-zu2};
    double vec2[3] = {xu3-xu2 , yu3-yu2 , zu3-zu2};

    d["angle"] =acos(
      (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]
      )/(
      sqrt(vec1[0] * vec1[0] + vec1[1] * vec1[1] + vec1[2] * vec1[2])*
      sqrt(vec2[0] * vec2[0] + vec2[1] * vec2[1] + vec2[2] * vec2[2])
      ));
  }

  datakeys.add("angle");
}

/* ------------------------------------------------------------------ */
