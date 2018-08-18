/* ---------------------------------------------------------------------
Processor: is an abstract class to process data.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "processor.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

template <class GEN>
void Processor::register_generators(ShPtr<GEN> gen)
{
  generators.push_back(gen);

  n_generators = generators.size();

  for (auto g : generators)
  {
    g->appoint();
  }
}

template void Processor::register_generators(
  ShPtr<GenElement> gen);
template void Processor::register_generators(
  ShPtr<GenDict> gen);
template void Processor::register_generators(
  ShPtr<GenList> gen);

/* ------------------------------------------------------------------ */

template <class GEN>
void Processor::register_generators(const List<ShPtr<GEN>> &gens)
{
  for (auto gen : gens)
  {
    generators.push_back(gen);
  }

  n_generators = generators.size();

  for (auto g : generators)
  {
    g->appoint();
  }
}

template void Processor::register_generators(
  const List<ShPtr<GenElement>> &gens);
template void Processor::register_generators(
  const List<ShPtr<GenDict>> &gens);
template void Processor::register_generators(
  const List<ShPtr<GenList>> &gens);

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

    if (ERROR_OCCURED) return true;

    run_impl(index);

    if (ERROR_OCCURED) return true;

    generators[index]->goodbye();

    if (ERROR_OCCURED) return true;

    return false;
  }
  else
  {
    return true;
  }
}
