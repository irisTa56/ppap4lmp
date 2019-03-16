/*!
  @file src/starters/sta_molecules.cpp
  @brief This file has an implementation of StaMolecules class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/07/07
*/

#include "sta_molecules.h"

/* ------------------------------------------------------------------ */

StaMolecules::StaMolecules(
  const ElPtr &el_atoms)
{
  ext_generator = el_atoms;
}

/* ------------------------------------------------------------------ */

void StaMolecules::compute_impl(
  Json &data)
{
  auto el_atoms = ext_generator->get_element();

  el_atoms->required_keys({"mol", "id"});

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
}

/* ------------------------------------------------------------------ */
