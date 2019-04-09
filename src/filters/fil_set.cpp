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
  const Map<Str,Set<Json>> &acceptable_value_sets_)
{
  acceptable_value_sets = acceptable_value_sets_;
}

/* ------------------------------------------------------------------ */

void FilSet::compute_impl(
  Json &data)
{
  for (const auto &item : acceptable_value_sets)
  {
    check_required_keys(item.first);
  }

  Json remaining_data = Json::array();

  for (const auto &d : data)
  {
    bool pass = true;

    for (const auto &item : acceptable_value_sets)
    {
      auto &set = item.second;

      if (set.find(d[item.first]) == set.end())  // value is in set?
      {
        pass = false;
        break;
      }
    }

    if (pass)
    {
      remaining_data.push_back(d);
    }
  }

  data.swap(remaining_data);
}

/* ------------------------------------------------------------------ */
