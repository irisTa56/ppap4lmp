/*!
  @file src/filters/fil_set.cpp
  @brief This file has an implementation of FilSet class,
  which is a subclass of Filter class.
  @author Takayuki Kobayashi
  @date 2018/07/01
*/

#include "fil_set.h"

/* ------------------------------------------------------------------ */

FilSet::FilSet(
  const Map<Str,Set<Json>> &value_sets_)
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
      auto &set = item.second;

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

/* ------------------------------------------------------------------ */
