/*!
  @file src/processors/pro_distance_in_molecule.cpp
  @brief This file has an implementation of ProDistanceInMolecule class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/08/25
*/

#include "pro_distance_in_molecule.h"
#include "../utils/map_to_index.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

ProDistanceInMolecule::ProDistanceInMolecule(
  const ElPtr &mols,
  const ElPtr &atoms)
{
  register_generator(ShPtr<GenDict>(
    new GenDict({{"Mols", mols}, {"Atoms", atoms}})));
}

/* ------------------------------------------------------------------ */

ProDistanceInMolecule::ProDistanceInMolecule(
  const Vec<std::pair<ElPtr,ElPtr>> &pairs)
{
  Vec<ShPtr<GenDict>> gens;

  for (const auto &pair : pairs)
  {
    gens.push_back(ShPtr<GenDict>(
      new GenDict({{"Mols", pair.first}, {"Atoms", pair.second}})));
  }

  register_generators(gens);
}

/* ------------------------------------------------------------------ */

void ProDistanceInMolecule::run_impl(
  const int index)
{
  auto el_mols = generators[index]->get_element("Mols");

  el_mols->required("atom-ids");

  auto &mols = el_mols->get_data();

  auto el_atoms = generators[index]->get_element("Atoms");

  // NOTE: `id` property is required to ensure data is sorted.
  el_atoms->required({"xu", "yu", "zu", "id"});

  auto &atoms = el_atoms->get_data();

  auto id2index_atom = ut::map_to_index(atoms, "id");

  Vec<double> distance2_tmp;

  for (const auto &mol : mols)
  {
    if (mol.value("type", 1) != target_moltype) continue;

    auto &atom_ids = mol["atom-ids"];

    auto &atom1 = atoms[id2index_atom[atom_ids.at(index1_in_mol)]];
    auto &atom2 = atoms[id2index_atom[atom_ids.at(index2_in_mol)]];

    auto dx = atom2["xu"].get<double>() - atom1["xu"].get<double>();
    auto dy = atom2["yu"].get<double>() - atom1["yu"].get<double>();
    auto dz = atom2["zu"].get<double>() - atom1["zu"].get<double>();

    distance2_tmp.push_back(dx*dx+dy*dy+dz*dz);
  }

  distance2_traj[index] = RowArrayXd::Map(
    distance2_tmp.data(), distance2_tmp.size());
}

/* ------------------------------------------------------------------ */

void ProDistanceInMolecule::prepare()
{
  distance2_traj.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProDistanceInMolecule::finish()
{
  auto size = distance2_traj.front().size();

  for (const auto &d2 : distance2_traj)
  {
    if (size != d2.size())
    {
      ut::runtime_error("Data sizes must be the same");
    }
  }

  distance2_array = ArrayXXd(n_generators, size);

  for (int i = 0; i != n_generators; ++i)
  {
    distance2_array.row(i) = distance2_traj[i];
  }

  distance2_traj.clear();
  distance2_traj.shrink_to_fit();
}

/* ------------------------------------------------------------------ */

void ProDistanceInMolecule::set_indices(
  int index1_in_mol_,
  int index2_in_mol_)
{
  index1_in_mol = index1_in_mol_;
  index2_in_mol = index2_in_mol_;
}

/* ------------------------------------------------------------------ */

void ProDistanceInMolecule::set_moltype(
  int target_moltype_)
{
  target_moltype_ = target_moltype;
}

/* ------------------------------------------------------------------ */

ArrayXXd ProDistanceInMolecule::get_distance_array()
{
  return distance2_array.sqrt();
}

/* ------------------------------------------------------------------ */

const ArrayXXd &ProDistanceInMolecule::get_distance2_array()
{
  return distance2_array;
}

/* ------------------------------------------------------------------ */
