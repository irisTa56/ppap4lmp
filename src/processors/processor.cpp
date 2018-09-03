/* ---------------------------------------------------------------------
Processor: is an abstract class to process data.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "processor.h"

/* ------------------------------------------------------------------ */

template <class GEN>
void Processor::register_generator(
  const ShPtr<GEN> &gen)
{
  generators.clear();

  generators.push_back(gen);

  n_generators = generators.size();

  for (const auto &g : generators)
  {
    g->appoint();
  }
}

template void Processor::register_generator(
  const ShPtr<Element> &gen);
template void Processor::register_generator(
  const ShPtr<GenDict> &gen);
template void Processor::register_generator(
  const ShPtr<GenList> &gen);

/* ------------------------------------------------------------------ */

template <class GEN>
void Processor::register_generators(
  const Vec<ShPtr<GEN>> &gens)
{
  generators.clear();

  for (const auto &gen : gens)
  {
    generators.push_back(gen);
  }

  n_generators = generators.size();

  for (const auto &g : generators)
  {
    g->appoint();
  }
}

template void Processor::register_generators(
  const Vec<ShPtr<Element>> &gens);
template void Processor::register_generators(
  const Vec<ShPtr<GenDict>> &gens);
template void Processor::register_generators(
  const Vec<ShPtr<GenList>> &gens);

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

  return true;
}
