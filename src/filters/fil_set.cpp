/* ---------------------------------------------------------------------
FilSet: stands for Filter using Set of values.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "fil_set.h"
#include "../utils.h"

/* ------------------------------------------------------------------ */

FilSet::FilSet(
  const Dict<Str,Set<Json>> &value_sets_)
{
  value_sets = value_sets_;
}

/* ------------------------------------------------------------------ */

FilSet::FilSet(
  ShPtr<GenElement> elem,
  const Dict<Str,Set<Json>> &value_sets_) : Filter(elem)
{
  value_sets = value_sets_;
}

/* ------------------------------------------------------------------ */

void FilSet::compute_impl(
  Json &data,
  Set<Str> &datakeys)
{
  for (const auto &item : value_sets)
  {
    check_key(datakeys, item.first);
  }

  Json tmp;

  for (auto &d : data)
  {
    bool pass = true;

    for (const auto &item : value_sets)
    {
      auto set = item.second;

      if (set.find(d[item.first]) == set.end())
      {
        pass = false;
        break;
      }
    }

    if (pass)
    {
      tmp.push_back(d);
    }
  }

  data.swap(tmp);
}
