/*!
  @file src/core/gen_list.cpp
  @brief This file has implementations of the GenList class.
  @author Takayuki Kobayashi
  @date 2018/07/03
  @details \e GenList stands for Generator List (or vector). Please see
  the header file for more details.
*/

#include "gen_list.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */
/* NOTE:
  The following constructor is thread-unsafe. It is assumed to be not
  called from multithreads.
*/
GenList::GenList(
  const Vec<ShPtr<Generator>> &generator_list_)
{
  generator_list = generator_list_;

  for (const auto &gen : generator_list)
  {
    merge_update_chain(gen->get_update_chain());
  }
}

/* ------------------------------------------------------------------ */

ElPtr GenList::get_element(
  const Json &name)
{
  if (!name.is_number_integer())
  {
    ut::runtime_error("Rejection of non-integer Json");
  }

  return std::dynamic_pointer_cast<Element>(
    generator_list[name.get<int>()]);
}

/* ------------------------------------------------------------------ */

ShPtr<Generator> GenList::get_generator(
  const Json &name)
{
  if (!name.is_number_integer())
  {
    ut::runtime_error("Rejection of non-integer Json");
  }

  return generator_list[name.get<int>()];
}

/* ------------------------------------------------------------------ */

int GenList::get_length()
{
  return generator_list.size();
}