/* ---------------------------------------------------------------------
FilSet: stands for Filter using Set of values.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "fil_set.h"

/* ------------------------------------------------------------------ */

FilSet::FilSet(
  const Map<Str,Set<Json>> &value_sets_)
{
  value_sets = value_sets_;
}

/* ------------------------------------------------------------------ */

FilSet::FilSet(
  const ShPtr<Element> &elem,
  const Map<Str,Set<Json>> &value_sets_) : Filter(elem)
{
  value_sets = value_sets_;
}

/* ------------------------------------------------------------------ */

void FilSet::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  for (const auto &item : value_sets)
  {
    datakeys.required(item.first);
  }

  Json tmp = Json::array();

  for (const auto &d : data)
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
