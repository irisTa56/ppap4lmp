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
  // Abstract beads without moltype is used as those for moltype 1
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

std::pair<bool,bool> StaBeads::check_mol_type_to_abst_beads()
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

  std::pair<bool,bool> tmp = std::make_pair(false, false);;

  if (type_counter == counter)
  {
    tmp.first = true;
  }
  else if (type_counter != 0)
  {
    runtime_error("The number of 'type' is invalid");
  }

  if (weights_counter == counter)
  {
    tmp.second = true;
  }
  else if (weights_counter != 0)
  {
    runtime_error("The number of 'weights' is invalid");
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

void StaBeads::compute_impl(
  Json &data,
  Set<Str> &datakeys)
{
  auto with_additional = check_mol_type_to_abst_beads();

  auto gen_mols = ext_generator->get_element();

  check_key(gen_mols, "atom-ids");

  auto &mols = gen_mols->get_data();

  int bead_id = 0;

  for (const auto &mol : mols)
  {
    auto &atom_ids = mol["atom-ids"];
    // If moltype is not set, default value (1) is used
    auto abst_beads = mol_type_to_abst_beads[mol.value("type", 1)];

    for (const auto &abst_bead : abst_beads)
    {
      Json tmp = {{"id", ++bead_id}, {"mol", mol["id"]}};

      Json ids_tmp;

      for (int index : abst_bead["indices-in-mol"])
      {
        ids_tmp.push_back(atom_ids.at(index));
      }

      tmp["atom-ids"].swap(ids_tmp);

      if (with_additional.first)
      {
        tmp["type"] = abst_bead["type"];
      }

      if (with_additional.second)
      {
        Json weights_tmp;

        for (double w : abst_bead["weights"])
        {
          weights_tmp.push_back(w);
        }

        tmp["atom-weights"].swap(weights_tmp);
      }

      data.push_back(tmp);
    }
  }

  datakeys.insert({"id", "mol", "atom-ids"});

  if (with_additional.first)
  {
    datakeys.insert("type");
  }

  if (with_additional.second)
  {
    datakeys.insert("atom-weights");
  }
}
