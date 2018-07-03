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

bool Processor::run()
{
  int index;

  #pragma omp critical (processor)
  {
    index = i_generator;
    i_generator++;
  }

  if (index < n_generators)
  {
    run_impl(index);
    generators[index]->goodbye();

    return false;
  }
  else
  {
    return true;
  }
}

/* ------------------------------------------------------------------ */

void Processor::prepare()
{
  for (auto g : generators)
  {
    g->appoint();
  }

  prepare_impl();
}
