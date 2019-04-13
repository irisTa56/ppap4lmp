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

const bool FilSet::check_if_pass_data_elem(
  const Json &elem_in_data)
{
  for (const auto &item : acceptable_value_sets)
  {
    auto &set = item.second;

    if (set.find(elem_in_data[item.first]) == set.end()) return false;
  }

  return true;
}

/* ------------------------------------------------------------------ */

void FilSet::compute_impl(
  Json &data,
  JsonToVoidFunc check_required_keys,
  JsonToBoolFunc check_optional_keys)
{
  for (const auto &item : acceptable_value_sets)
  {
    check_required_keys(item.first);
  }

  Json remaining_data = Json::array();

  for (const auto &d : data)
  {
    if (check_if_pass_data_elem(d))
    {
      remaining_data.push_back(d);
    }
  }

  data.swap(remaining_data);
}
