/*!
  @file src/starters/sta_beads.cpp
  @brief This file has an implementation of StaBeads class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/08/18
*/

#include "sta_beads.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

StaBeads::StaBeads(
  const ElPtr &el_mols,
  const Vec<Json> &scheme)
{
  ext_generator = el_mols;
  mol_type_to_abst_beads[1] = scheme;
}

/* ------------------------------------------------------------------ */

StaBeads::StaBeads(
  const ElPtr &el_mols,
  const Map<int,Vec<Json>> &schemes)
{
  ext_generator = el_mols;
  mol_type_to_abst_beads = schemes;
}

/* ------------------------------------------------------------------ */

std::pair<bool,bool> StaBeads::check_mol_type_to_abst_beads()
{
  int counter = 0;
  int type_counter = 0;
  int weights_counter = 0;

  for (const auto &item : mol_type_to_abst_beads)
  {
    for (const auto &abst_bead : item.second)
    {
      const auto it_end = abst_bead.cend();
      const auto it_index = abst_bead.find("indices-in-mol");

      if (it_index == it_end)
      {
        ut::runtime_error(
          "Mapping to beads must be specified by 'indices-in-mol'");
      }

      if (abst_bead.find("type") != it_end)
      {
        type_counter++;
      }

      auto it_weights = abst_bead.find("weights");

      if (it_weights != it_end)
      {
        if ((*it_index).size() != (*it_weights).size())
        {
          ut::runtime_error(
            "The numbers of elements in 'indices-in-mol' and 'weights' "
            "are inconsistent");
        }

        weights_counter++;
      }

      counter++;
    }
  }

  std::pair<bool,bool> have_type_andor_weights = std::make_pair(false, false);

  if (type_counter == counter)
  {
    // all the beads have 'type' attribute
    have_type_andor_weights.first = true;
  }
  else if (type_counter != 0)
  {
    ut::runtime_error("The number of 'type' is invalid");
  }

  if (weights_counter == counter)
  {
    // all the beads have 'weights' attribute
    have_type_andor_weights.second = true;
  }
  else if (weights_counter != 0)
  {
    ut::runtime_error("The number of 'weights' is invalid");
  }

  return have_type_andor_weights;
}

/* ------------------------------------------------------------------ */

void StaBeads::compute_impl(
  Json &data,
  JsonToVoidFunc check_required_keys,
  JsonToBoolFunc check_optional_keys)
{
  auto have_type_andor_weights = check_mol_type_to_abst_beads();

  auto el_mols = ext_generator->get_element();

  el_mols->check_required_keys("atom-ids");

  auto &mols = el_mols->get_data();

  int bead_id = 0;

  for (const auto &mol : mols)
  {
    auto &atom_ids = mol["atom-ids"];
    auto &abst_beads = mol_type_to_abst_beads[mol.value("type", 1)];

    for (const auto &abst_bead : abst_beads)
    {
      data.push_back({{"id", ++bead_id}, {"mol", mol["id"]}});

      auto &back = data.back();

      auto &ids_ref = back["atom-ids"];

      for (const int &index : abst_bead["indices-in-mol"])
      {
        ids_ref.push_back(atom_ids.at(index));
      }

      if (have_type_andor_weights.first)
      {
        back["type"] = abst_bead["type"];
      }

      if (have_type_andor_weights.second)
      {
        back["atom-weights"] = abst_bead["weights"];
      }
    }
  }
}
