/* ---------------------------------------------------------------------
Processor: is an abstract class to process data.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "processor.h"

/* ------------------------------------------------------------------ */

void Processor::register_generators(const List<ShPtr<Generator>> &gens)
{
  generators = gens;
  n_generators = generators.size();

  for (auto g : generators)
  {
    g->appoint();
  }
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
    generators[index]->hello();
    run_impl(index);
    generators[index]->goodbye();

    return false;
  }
  else
  {
    return true;
  }
}
