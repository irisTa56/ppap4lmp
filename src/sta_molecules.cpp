/* ---------------------------------------------------------------------
StaMolecules: stands for Starter to generate Molecules from Atoms.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "sta_molecules.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

StaMolecules::StaMolecules(std::shared_ptr<Generator> gen)
{
  if (gen->get_datatype() == "Atoms")
  {
    reference_generator = gen;
  }
  else
  {
    runtime_error(
      "StaMolecules cannot use " + gen->get_dataname());
  }

  datatype_to_be_initialized = "Molecules";
}

/* ------------------------------------------------------------------ */

void StaMolecules::compute_impl(json &data)
{
  if (!check_key(reference_generator->get_data(), "mol"))
  {
    runtime_error(
      reference_generator->get_dataname() + " does not have 'mol'");
  }

  auto &atoms = reference_generator->get_data();

  std::unordered_map<int,int> id_to_index;

  int max_index = 0;

  for (const auto &atom : atoms)
  {
    int molid = atom["mol"];

    if (id_to_index.find(molid) == id_to_index.end())
    {
      data[max_index]["id"] = molid;
      id_to_index[molid] = max_index;

      max_index++;
    }

    data[id_to_index[molid]]["atom-ids"].push_back(atom["id"]);
  }
}