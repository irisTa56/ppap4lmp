/*!
  @file src/starters/sta_custom.cpp
  @brief This file has an implementation of StaCustom class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/08/16
*/

#include "sta_custom.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

StaCustom::StaCustom(
  const Json &json_)
{
  json = json_;
}

/* ------------------------------------------------------------------ */

void StaCustom::compute_impl(
  Json &data,
  JsonToVoidFunc check_required_keys,
  JsonToBoolFunc check_optional_keys)
{
  if (json.is_array())
  {
    Vec<Str> jsonkeys;

    for (const auto &el : json.front().items())
    {
      jsonkeys.push_back(el.key());
    }

    for (const auto &j : json)
    {
      for (auto it = j.cbegin(); it != j.cend(); ++it)
      {
        if (it.key() != jsonkeys[std::distance(j.cbegin(), it)])
        {
          ut::runtime_error("Invalid key(s) in array data");
        }
      }
    }
  }

  data = json;
}
