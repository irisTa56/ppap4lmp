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

void ProTimeCorrelationInMolecule::compute_temporary_vectors(
  std::function<void(const RowVector3d &)> callback,
  const ElPtr &el_mols,
  const ElPtr &el_atoms)
{
  // NOTE: `id` property is check_required_keys to ensure data is sorted.
  el_mols->check_required_keys({"id", "atom-ids"});

  auto &mols = el_mols->get_data();

  el_atoms->check_required_keys({"id", "xu", "yu", "zu"});

  auto &atoms = el_atoms->get_data();

  auto id2index_atom = ut::map_to_index(atoms, "id");

  for (const auto &mol : mols)
  {
    if (mol.value("type", 1) != target_moltype) continue;

    auto &atom_ids = mol["atom-ids"];

    auto &atom1 = atoms[id2index_atom[atom_ids.at(index1_in_mol)]];
    auto &atom2 = atoms[id2index_atom[atom_ids.at(index2_in_mol)]];

    RowVector3d vector_tmp;
    vector_tmp << atom2["xu"].get<double>() - atom1["xu"].get<double>(),
                   atom2["yu"].get<double>() - atom1["yu"].get<double>(),
                   atom2["zu"].get<double>() - atom1["zu"].get<double>();

    callback(vector_tmp);
  }
}

/* ------------------------------------------------------------------ */

void ProTimeCorrelationInMolecule::run_impl(
  const int index)
{
  Vec<double> coefficients_tmp;

  compute_temporary_vectors(
    [this, &coefficients_tmp](const RowVector3d &vec)
    {
      auto index = coefficients_tmp.size();
      coefficients_tmp.push_back(
        initial_vectors[index].dot(vec)
          /* normalize */ * initial_reciprocal_norm2[index]);
    },
    generators[index]->get_element("Mols"),
    generators[index]->get_element("Atoms"));

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
  use_generator_at(0);

  compute_temporary_vectors(
    [this](const RowVector3d &vec)
    {
      initial_vectors.push_back(vec);
      initial_reciprocal_norm2.push_back(1.0/vec.dot(vec));
    },
    generators.front()->get_element("Mols"),
    generators.front()->get_element("Atoms"));

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
  target_moltype = target_moltype_;
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
