/*!
  @file src/core/gen_dict.cpp
  @brief This file has an implementation of GenDict class.
  @author Takayuki Kobayashi
  @date 2018/07/03
*/

#include "gen_dict.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

GenDict::GenDict(
  const Map<Str,ShPtr<Generator>> &generator_dict_)
{
  generator_dict = generator_dict_;

  for (const auto &item : generator_dict)
  {
    merge_update_chain(item.second->get_update_chain());
  }
}

/* ------------------------------------------------------------------ */

ElPtr GenDict::get_element(
  const Json &name)
{
  if (!name.is_string())
  {
    ut::runtime_error("Rejection of non-string Json");
  }

  return std::dynamic_pointer_cast<Element>(
    generator_dict[name.get<Str>()]);
}

/* ------------------------------------------------------------------ */

ShPtr<Generator> GenDict::get_generator(
  const Json &name)
{
  if (!name.is_string())
  {
    ut::runtime_error("Rejection of non-string Json");
  }

  return generator_dict[name.get<Str>()];
}

/* ------------------------------------------------------------------ */

void GenDict::accessed_by_instance_of(
  const Str &classname)
{
  for (const auto &item : generator_dict)
  {
    item.second->accessed_by_instance_of(classname);
  }
}

/* ------------------------------------------------------------------ */

Set<Str> GenDict::get_keys()
{
  Set<Str> keys;

  for (const auto &item : generator_dict)
  {
    keys.insert(item.first);
  }

  return keys;
}

/* ------------------------------------------------------------------ */
