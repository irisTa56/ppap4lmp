/*!
  @file src/core/gen_list.cpp
  @brief This file has an implementation of GenList class.
  @author Takayuki Kobayashi
  @date 2018/07/03
  @details For more details, please see the header file,
  src/core/gen_list.h.
*/

#include "gen_list.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

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

/* ------------------------------------------------------------------ */
