/* ---------------------------------------------------------------------
Processor: is an abstract class to process data.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "processor.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

template <class GEN>
void Processor::register_generator(
  ShPtr<GEN> gen)
{
  generators.clear();

  generators.push_back(gen);

  n_generators = generators.size();

  for (auto g : generators)
  {
    g->appoint();
  }
}

template void Processor::register_generator(
  ShPtr<GenElement> gen);
template void Processor::register_generator(
  ShPtr<GenDict> gen);
template void Processor::register_generator(
  ShPtr<GenList> gen);

/* ------------------------------------------------------------------ */

template <class GEN>
void Processor::register_generators(
  const List<ShPtr<GEN>> &gens)
{
  generators.clear();

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
    index = i_generator++;
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
