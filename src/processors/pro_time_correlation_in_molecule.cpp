/*!
  @file src/processors/pro_time_correlation_in_molecule.cpp
  @brief This file has an implementation of ProTimeCorrelationInMolecule class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/10/24
*/

#include "pro_time_correlation_in_molecule.h"
#include "../utils/map_to_index.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

ProTimeCorrelationInMolecule::ProTimeCorrelationInMolecule(
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

void ProTimeCorrelationInMolecule::run_impl(
  const int index)
{
  auto el_mols = generators[index]->get_element("Mols");

  // NOTE: `id` property is required to ensure data is sorted.
  el_mols->required({"id", "atom-ids"});

  auto &mols = el_mols->get_data();

  auto el_atoms = generators[index]->get_element("Atoms");

  el_atoms->required({"id", "xu", "yu", "zu"});

  auto &atoms = el_atoms->get_data();

  auto id2index_atom = ut::map_to_index(atoms, "id");

  Vec<double> coefficients_tmp;

  int i_target = 0;

  for (const auto &mol : mols)
  {
    if (mol.value("type", 1) != target_moltype) continue;

    auto &atom_ids = mol["atom-ids"];

    auto &atom1 = atoms[id2index_atom[atom_ids.at(index1_in_mol)]];
    auto &atom2 = atoms[id2index_atom[atom_ids.at(index2_in_mol)]];

    coefficients_tmp.push_back(initial_vectors[i_target].dot(
      (RowVector3d() <<
        atom2["xu"].get<double>() - atom1["xu"].get<double>(),
        atom2["yu"].get<double>() - atom1["yu"].get<double>(),
        atom2["zu"].get<double>() - atom1["zu"].get<double>()
      ).finished()) * initial_reciprocal_norm2[i_target]);

    i_target++;
  }

  if (coefficients_tmp.size() != initial_vectors.size())
  {
    ut::runtime_error(
      "Number of molecules and molecular types must be unchanged");
  }

  coefficients_traj[index] = RowArrayXd::Map(
    coefficients_tmp.data(), coefficients_tmp.size());
}

/* ------------------------------------------------------------------ */

void ProTimeCorrelationInMolecule::prepare()
{
  generators.front()->hello();

  auto el_initial_mols = generators.front()->get_element("Mols");

  // NOTE: `id` property is required to ensure data is sorted.
  el_initial_mols->required({"id", "atom-ids"});

  auto &mols = el_initial_mols->get_data();

  auto el_initial_atoms = generators.front()->get_element("Atoms");

  el_initial_atoms->required({"id", "xu", "yu", "zu"});

  auto &atoms = el_initial_atoms->get_data();

  auto id2index_atom = ut::map_to_index(atoms, "id");

  for (const auto &mol : mols)
  {
    if (mol.value("type", 1) != target_moltype) continue;

    auto &atom_ids = mol["atom-ids"];

    auto &atom1 = atoms[id2index_atom[atom_ids.at(index1_in_mol)]];
    auto &atom2 = atoms[id2index_atom[atom_ids.at(index2_in_mol)]];

    initial_vectors.push_back(
      (RowVector3d() <<
        atom2["xu"].get<double>() - atom1["xu"].get<double>(),
        atom2["yu"].get<double>() - atom1["yu"].get<double>(),
        atom2["zu"].get<double>() - atom1["zu"].get<double>()
      ).finished());

    initial_reciprocal_norm2.push_back(
      1.0/initial_vectors.back().dot(initial_vectors.back()));
  }

  coefficients_traj.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProTimeCorrelationInMolecule::finish()
{
  coefficients_array = ArrayXXd(n_generators, initial_vectors.size());

  for (int i = 0; i != n_generators; ++i)
  {
    coefficients_array.row(i) = coefficients_traj[i];
  }

  time_correlation_function = coefficients_array.rowwise().mean();

  initial_vectors.clear();
  initial_vectors.shrink_to_fit();
  initial_reciprocal_norm2.clear();
  initial_reciprocal_norm2.shrink_to_fit();
  coefficients_traj.clear();
  coefficients_traj.shrink_to_fit();
}

/* ------------------------------------------------------------------ */

void ProTimeCorrelationInMolecule::set_indices(
  int index1_in_mol_,
  int index2_in_mol_)
{
  index1_in_mol = index1_in_mol_;
  index2_in_mol = index2_in_mol_;
}

/* ------------------------------------------------------------------ */

void ProTimeCorrelationInMolecule::set_moltype(
  int target_moltype_)
{
  target_moltype_ = target_moltype;
}
/* ------------------------------------------------------------------ */

const ArrayXXd &ProTimeCorrelationInMolecule::get_coefficients_array()
{
  return coefficients_array;
}

/* ------------------------------------------------------------------ */

const ArrayXd &ProTimeCorrelationInMolecule::get_time_correlation()
{
  return time_correlation_function;
}

/* ------------------------------------------------------------------ */
