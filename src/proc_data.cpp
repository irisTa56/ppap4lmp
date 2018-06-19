/* ---------------------------------------------------------------------
This file is for ProcData class.

create: 2018/06/18 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "proc_data.h"

/* ------------------------------------------------------------------ */

void ProcData::prepare() {

  results.resize(length);

  for(Extractor *e : extractors) {
    e->reserve();
  }

}

/* ------------------------------------------------------------------ */

void ProcData::run(int itr) {

  results[itr] = extractors[itr]->get_data();

  //if (extractors[itr]->del_data()) { /* data will be used in Python */ }

}

/* ------------------------------------------------------------------ */

void ProcData::dry_run(int itr) {

  extractors[itr]->cancel();

}

/* ------------------------------------------------------------------ */

const std::vector<Data *> &ProcData::get_results() {

  return results;

}
