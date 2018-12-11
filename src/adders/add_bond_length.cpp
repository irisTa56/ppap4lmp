/*!
  @file src/adders/add_bond_length.cpp
  @brief This file has an implementation of AddBondLength class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/13
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
  Json &data,
  DataKeys &datakeys)
{
  datakeys.required({"atom1-id", "atom2-id"});

  auto el_atoms = ext_generator->get_element();

  el_atoms->required({"id", "xu", "yu", "zu"});

  auto &atoms = el_atoms->get_data();

  auto id2index_atom = ut::map_to_index(atoms, "id");

  for (auto &d : data)
  {
    auto index1 = id2index_atom[d["atom1-id"]];
    auto index2 = id2index_atom[d["atom2-id"]];
    auto &atom1 = atoms[index1];
    auto &atom2 = atoms[index2];
    double xu1 = atom1["xu"];
    double xu2 = atom2["xu"];
    double yu1 = atom1["yu"];
    double yu2 = atom2["yu"];
    double zu1 = atom1["zu"];
    double zu2 = atom2["zu"];

    d["length"] = sqrt(
        (xu2-xu1)*(xu2-xu1) + (yu2-yu1)*(yu2-yu1) + (zu2-zu1)*(zu2-zu1));
  }

  datakeys.add("length");
}

/* ------------------------------------------------------------------ */
