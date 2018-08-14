/* ---------------------------------------------------------------------
GenDict: stands for Generator Dictionary containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <algorithm>

#include "gen_dict.h"
#include "utils.h"

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
GenDict::GenDict(const Dict<Str,ShPtr<Generator>> &generator_dict_)
{
  generator_dict = generator_dict_;

  for (const auto &item : generator_dict)
  {
    merge_update_chain(item.second->get_update_chain());
  }
}

/* ------------------------------------------------------------------ */

ShPtr<GenElement> GenDict::get_element(Json name)
{
  if (!name.is_string())
  {
    runtime_error("GenDict::get_element accepts a string only");
  }

  return std::dynamic_pointer_cast<GenElement>(
    generator_dict[name.get<Str>()]);
}

/* ------------------------------------------------------------------ */

ShPtr<Generator> GenDict::get_generator(Json name)
{
  if (!name.is_string())
  {
    runtime_error("GenDict::get_generator accepts a string only");
  }

  return generator_dict[name.get<Str>()];
}

/* ------------------------------------------------------------------ */

const Set<Str> GenDict::get_keys()
{
  Set<Str> tmp;

  for (const auto &item : generator_dict)
  {
    tmp.insert(item.first);
  }

  return tmp;
}
