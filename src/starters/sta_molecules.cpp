/* ---------------------------------------------------------------------
StaMolecules: stands for Starter to generate Molecules from atoms.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "sta_molecules.h"

/* ------------------------------------------------------------------ */

StaMolecules::StaMolecules(
  const ShPtr<Element> &el_atoms)
{
  ext_generator = el_atoms;
}

/* ------------------------------------------------------------------ */

void StaMolecules::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  auto el_atoms = ext_generator->get_element();

  el_atoms->required({"mol", "id"});

  auto &atoms = el_atoms->get_data();

  Map<int,int> id2index;

  int max_index = 0;

  for (const auto &atom : atoms)
  {
    int molid = atom["mol"];

    if (id2index.find(molid) == id2index.end())
    {
      data[max_index]["id"] = molid;
      id2index[molid] = max_index++;
    }

    data[id2index[molid]]["atom-ids"].push_back(atom["id"]);
  }

  datakeys.add({"id", "atom-ids"});
}