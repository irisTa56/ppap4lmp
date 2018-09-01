/* ---------------------------------------------------------------------
GenList: stands for Generator List containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "gen_list.h"
#include "../utils.h"

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
GenList::GenList(
  const List<ShPtr<Generator>> &generator_list_)
{
  generator_list = generator_list_;

  for (auto gen : generator_list)
  {
    merge_update_chain(gen->get_update_chain());
  }
}

/* ------------------------------------------------------------------ */

ShPtr<GenElement> GenList::get_element(
  Json name)
{
  if (!name.is_number_integer())
  {
    runtime_error("GenList::get_element accepts an integer only");
  }

  return std::dynamic_pointer_cast<GenElement>(
    generator_list[name.get<int>()]);
}

/* ------------------------------------------------------------------ */

ShPtr<Generator> GenList::get_generator(
  Json name)
{
  if (!name.is_number_integer())
  {
    runtime_error("GenList::get_generator accepts an integer only");
  }

  return generator_list[name.get<int>()];
}

/* ------------------------------------------------------------------ */

const int GenList::get_length()
{
  return generator_list.size();
}