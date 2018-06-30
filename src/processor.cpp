/* ---------------------------------------------------------------------
Processor: is an abstract class to process data.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "processor.h"

/* ------------------------------------------------------------------ */

Processor::Processor(std::shared_ptr<Generator> gen)
{
  generators.push_back(gen);
  n_generators = generators.size();
}

/* ------------------------------------------------------------------ */

Processor::Processor(std::vector<std::shared_ptr<Generator>> gens)
{
  generators = gens;
  n_generators = generators.size();
}

/* ------------------------------------------------------------------ */

void Processor::run(int i_generator)
{
  generators[i_generator]->hello();

  run_impl(i_generator);

  generators[i_generator]->goodbye();
}

/* ------------------------------------------------------------------ */

void Processor::prepare()
{
  for(auto g : generators)
  {
    g->appoint();
  }

  prepare_impl();
}

/* ------------------------------------------------------------------ */

void Processor::finish()
{
  finish_impl();
}

/* ------------------------------------------------------------------ */

const int Processor::get_n_generators()
{
  return n_generators;
}
