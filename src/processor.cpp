/* ---------------------------------------------------------------------
This file is for Processor class.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "processor.h"

/* ------------------------------------------------------------------ */

Processor::Processor(std::shared_ptr<Generator> gen) {

  generators.push_back(gen);
  n_generators = generators.size();

}

/* ------------------------------------------------------------------ */

Processor::Processor(std::vector<std::shared_ptr<Generator>> gens) {

  generators = gens;
  n_generators = generators.size();

}

/* ------------------------------------------------------------------ */

const int Processor::get_n_generators() {

  return n_generators;

}
