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
  mol_type_to_sbondses_in_mol[1] = scheme;
}

/* ------------------------------------------------------------------ */

AddSpecialBonds::AddSpecialBonds(
  const ElPtr &el_mols,
  const Map<int,Vec<Vec<int>>> &schemes)
{
  ext_generator = el_mols;
  mol_type_to_sbondses_in_mol = schemes;
}

/* ------------------------------------------------------------------ */

void AddSpecialBonds::compute_impl(
  Json &data)
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
    auto sbondses_in_mol
      = mol_type_to_sbondses_in_mol[mol.value("type", 1)];

    auto n_atoms_in_mol = atom_ids.size();

    if (sbondses_in_mol.size() != n_atoms_in_mol)
    {
      ut::runtime_error(
        "The numbers of atoms in a molecule are inconsistent");
    }

    for (int i = 0; i != n_atoms_in_mol; ++i)
    {
      auto tmp = Json::array();

      for (const int &index: sbondses_in_mol[i])
      {
        tmp.push_back(atom_ids.at(index));
      }

      data[id2index[atom_ids[i]]]["special-bonds"].swap(tmp);
    }
  }
}

/* ------------------------------------------------------------------ */
