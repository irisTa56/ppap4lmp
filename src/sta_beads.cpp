/* ---------------------------------------------------------------------
StaBeads: stands for Starter to generate Beads from molecules.

create: 2018/08/18 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "sta_beads.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

StaBeads::StaBeads(
  ShPtr<GenElement> gen_mols,
  const List<Json> &scheme)
{
  ext_generator = gen_mols;
  mol_type_to_abst_beads[1] = scheme;
}

/* ------------------------------------------------------------------ */

StaBeads::StaBeads(
  ShPtr<GenElement> gen_mols,
  const Dict<int,List<Json>> &schemes)
{
  ext_generator = gen_mols;
  mol_type_to_abst_beads = schemes;
}

/* ------------------------------------------------------------------ */

void StaBeads::check_mol_type_to_abst_beads()
{
  int counter = 0;
  int type_counter = 0;
  int weights_counter = 0;

  for (const auto &item : mol_type_to_abst_beads)
  {
    for (const auto &abst_bead : item.second)
    {
      auto it_end = abst_bead.end();
      auto it_index = abst_bead.find("indices-in-mol");

      if (it_index == it_end)
      {
        runtime_error(
          "Mapping to Beads must be specified by 'indices-in-mol'");
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
          runtime_error(
            "The numbers of elements in 'indices-in-mol' and 'weights' "
            "are inconsistent");
        }

        weights_counter++;
      }

      counter++;
    }
  }

  if (type_counter == 0)
  {
    with_type = false;
  }
  else if (type_counter == counter)
  {
    with_type = true;
  }
  else
  {
    runtime_error("The number of 'type' is invalid");
  }

  if (weights_counter == 0)
  {
    with_weights = false;
  }
  else if (weights_counter == counter)
  {
    with_weights = true;
  }
  else
  {
    runtime_error("The number of 'weights' is invalid");
  }
}

/* ------------------------------------------------------------------ */

void StaBeads::compute_impl(
  Json &data,
  Set<Str> &datakeys)
{
  check_mol_type_to_abst_beads();

  auto gen_mols = ext_generator->get_element();

  check_key(gen_mols, "atom-ids");

  auto &mols = gen_mols->get_data();

  int bead_id = 0;

  for (const auto &mol : mols)
  {
    auto atom_ids = mol["atom-ids"];
    auto abst_beads = mol_type_to_abst_beads[mol.value("type", 1)];

    for (const auto &abst_bead : abst_beads)
    {
      Json tmp = {{"id", ++bead_id}, {"mol", mol["id"]}};

      for (int index : abst_bead["indices-in-mol"])
      {
        tmp["atom-ids"].push_back(atom_ids.at(index));
      }

      if (with_type)
      {
        tmp["type"] = abst_bead["type"];
      }

      if (with_weights)
      {
        for (double w : abst_bead["weights"])
        {
          tmp["atom-weights"].push_back(w);
        }
      }

      data.push_back(tmp);
    }
  }

  datakeys.insert({"id", "mol", "atom-ids"});

  if (with_type)
  {
    datakeys.insert("type");
  }

  if (with_weights)
  {
    datakeys.insert("atom-weights");
  }
}
