/* ---------------------------------------------------------------------
AddSpecialBonds: stands for Adder for Special Bonds.
See: https://lammps.sandia.gov/doc/special_bonds.html

create: 2018/08/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_special_bonds.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddSpecialBonds::AddSpecialBonds(
  ShPtr<GenElement> gen_mols, const List<List<int>> &scheme)
{
  ext_generator = gen_mols;
  mol_type_to_sbonds_list_in_mol[1] = scheme;
}

/* ------------------------------------------------------------------ */

AddSpecialBonds::AddSpecialBonds(
  ShPtr<GenElement> gen_mols, const Dict<int,List<List<int>>> &schemes)
{
  ext_generator = gen_mols;
  mol_type_to_sbonds_list_in_mol = schemes;
}

/* ------------------------------------------------------------------ */

void AddSpecialBonds::compute_impl(Json &data, Set<Str> &datakeys)
{
  auto gen_mols = ext_generator->get_element();

  if (!check_containment<Str>(gen_mols->get_keys(), "atom-ids"))
  {
    runtime_error("AddSpecialBonds needs 'atom-ids' externally");
    return;
  }

  auto &mols = gen_mols->get_data();

  auto id2index = get_map_to_index(data, "id");

  for (const auto &mol : mols)
  {
    auto atom_ids = mol["atom-ids"];
    auto sbonds_list_in_mol
      = mol_type_to_sbonds_list_in_mol[mol.value("type", 1)];

    int n_atoms_in_mol = atom_ids.size();

    if (sbonds_list_in_mol.size() != n_atoms_in_mol)
    {
      runtime_error(
        "The numbers of atoms in a molecule are inconsistent");
      return;
    }

    for (int i = 0; i != n_atoms_in_mol; ++i)
    {
      auto &atom = data[id2index[atom_ids[i]]];

      for (int index: sbonds_list_in_mol[i])
      {
        atom["special-bonds"].push_back(atom_ids.at(index));
      }
    }
  }

  datakeys.insert("special-bonds");
}
