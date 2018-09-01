/* ---------------------------------------------------------------------
AddSpecialBonds: stands for Adder for Special Bonds.
See: https://lammps.sandia.gov/doc/special_bonds.html

create: 2018/08/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_special_bonds.h"
#include "../utils.h"

/* ------------------------------------------------------------------ */

AddSpecialBonds::AddSpecialBonds(
  ShPtr<GenElement> gen_mols,
  const List<List<int>> &scheme)
{
  ext_generator = gen_mols;
  // Special bonds list without moltype is used as that for moltype 1
  mol_type_to_sbondses_in_mol[1] = scheme;
}

/* ------------------------------------------------------------------ */

AddSpecialBonds::AddSpecialBonds(
  ShPtr<GenElement> gen_mols,
  const Dict<int,List<List<int>>> &schemes)
{
  ext_generator = gen_mols;
  mol_type_to_sbondses_in_mol = schemes;
}

/* ------------------------------------------------------------------ */

void AddSpecialBonds::compute_impl(
  Json &data,
  Set<Str> &datakeys)
{
  auto gen_mols = ext_generator->get_element();

  check_key(gen_mols, "atom-ids");

  if (check_containment<Str>(datakeys, "special-bonds"))
  {
    runtime_error("AddSpecialBonds cannot overwrite 'special-bonds'");
  }

  auto &mols = gen_mols->get_data();

  auto id2index = get_map_to_index(data, "id");

  for (const auto &mol : mols)
  {
    auto &atom_ids = mol["atom-ids"];
    // If moltype is not set, default value (1) is used
    auto sbondses_in_mol
      = mol_type_to_sbondses_in_mol[mol.value("type", 1)];

    auto n_atoms_in_mol = atom_ids.size();

    if (sbondses_in_mol.size() != n_atoms_in_mol)
    {
      runtime_error(
        "The numbers of atoms in a molecule are inconsistent");
    }

    for (int i = 0; i != n_atoms_in_mol; ++i)
    {
      Json tmp;

      for (int index: sbondses_in_mol[i])
      {
        tmp.push_back(atom_ids.at(index));
      }

      data[id2index[atom_ids[i]]]["special-bonds"].swap(tmp);
    }
  }

  datakeys.insert("special-bonds");
}
