/*!
  @file src/adders/add_special_bonds.cpp
  @brief This file has an implementation of AddSpecialBonds class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#include "add_special_bonds.h"
#include "../utils/map_to_index.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddSpecialBonds::AddSpecialBonds(
  const ElPtr &el_mols,
  const Vec<Vec<int>> &scheme)
{
  ext_generator = el_mols;
  mol_type_to_sbonds_list_in_mol[1] = scheme;
}

/* ------------------------------------------------------------------ */

AddSpecialBonds::AddSpecialBonds(
  const ElPtr &el_mols,
  const Map<int,Vec<Vec<int>>> &type_to_scheme)
{
  ext_generator = el_mols;
  mol_type_to_sbonds_list_in_mol = type_to_scheme;
}

/* ------------------------------------------------------------------ */

void AddSpecialBonds::compute_impl(
  Json &data,
  JsonToVoidFunc check_required_keys,
  JsonToBoolFunc check_optional_keys)
{
  if (check_optional_keys("special-bonds"))
  {
    ut::runtime_error("Key 'special-bonds' already exists");
  }

  auto el_mols = ext_generator->get_element();

  el_mols->check_required_keys("atom-ids");

  auto &mols = el_mols->get_data();

  auto id2index = ut::map_to_index(data, "id");

  for (const auto &mol : mols)
  {
    auto &atom_ids = mol["atom-ids"];
    auto sbonds_list_in_mol
      = mol_type_to_sbonds_list_in_mol[mol.value("type", 1)];

    auto n_atoms_in_mol = atom_ids.size();

    if (sbonds_list_in_mol.size() != n_atoms_in_mol)
    {
      ut::runtime_error(
        "The numbers of atoms in a molecule are inconsistent");
    }

    for (int i = 0; i != n_atoms_in_mol; ++i)
    {
      auto absolute_sbonds = Json::array();

      for (const int &index: sbonds_list_in_mol[i])
      {
        // convert relative index in a molecule to absolute atom id
        absolute_sbonds.push_back(atom_ids.at(index));
      }

      data[id2index[atom_ids[i]]]["special-bonds"].swap(absolute_sbonds);
    }
  }
}
