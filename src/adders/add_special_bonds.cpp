/* ---------------------------------------------------------------------
AddSpecialBonds: stands for Adder for Special Bonds.
See: https://lammps.sandia.gov/doc/special_bonds.html

create: 2018/08/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

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
  // Special bonds list without moltype is used as that for moltype 1
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
  Json &data,
  DataKeys &datakeys)
{
  if (datakeys.optional("special-bonds"))
  {
    ut::runtime_error("Key 'special-bonds' already exists");
  }

  auto el_mols = ext_generator->get_element();

  el_mols->required("atom-ids");

  auto &mols = el_mols->get_data();

  auto id2index = ut::map_to_index(data, "id");

  for (const auto &mol : mols)
  {
    auto &atom_ids = mol["atom-ids"];
    // If moltype is not set, default value (1) is used
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
      Json &sbonds = data[id2index[atom_ids[i]]]["special-bonds"];

      for (const int index: sbondses_in_mol[i])
      {
        sbonds.push_back(atom_ids.at(index));
      }
    }
  }

  datakeys.add("special-bonds");
}
