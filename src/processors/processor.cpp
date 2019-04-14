/*!
  @file src/processors/processor.cpp
  @brief This file has an implementation of Processor class,
  where an analysis process is programmed.
  @author Takayuki Kobayashi
  @date 2018/06/22
*/

#include <stdio.h>

#include "processor.h"

/* ------------------------------------------------------------------ */

template <class GEN>
void Processor::register_generator(
  const ShPtr<GEN> &gen)
{
  generators.clear();

  generators.push_back(gen);

  n_generators = generators.size();
}

template void Processor::register_generator(
  const ElPtr &gen);
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
}

template void Processor::register_generators(
  const Vec<ElPtr> &gens);
template void Processor::register_generators(
  const Vec<ShPtr<GenDict>> &gens);
template void Processor::register_generators(
  const Vec<ShPtr<GenList>> &gens);

/* ------------------------------------------------------------------ */

void Processor::use_generator_at(
  const int i)
{
  generators[i]->generate_data();
  generators[i]->accessed_by_instance_of(
    abi::__cxa_demangle(typeid(*this).name(), 0, 0, new int()));
}

/* ------------------------------------------------------------------ */

void Processor::finish_using_generator_at(
  const int i)
{
  generators[i]->finish_using_generated_data();
}

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
    use_generator_at(index);

    run_impl(index);

    finish_using_generator_at(index);

    return false;
  }

  return true;
}

/* ------------------------------------------------------------------ */

void Processor::startup()
{
  #pragma omp critical (processor)
  {
    i_generator = 0;
  }

  for (const auto &g : generators)
  {
    g->book_to_generate_data();
  }
}
