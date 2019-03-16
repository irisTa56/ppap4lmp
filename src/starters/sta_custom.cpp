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
  Json &data)
{
  Set<Str> jsonkeys;

  auto front = json.is_array() ? json.front() : json;

  for (auto it = front.begin(); it != front.end(); ++it)
  {
    jsonkeys.insert(it.key());
  }

  if (json.is_array())
  {
    for (const auto &j : json)
    {
      Set<Str> tmpkeys;

      for (auto it = j.begin(); it != j.end(); ++it)
      {
        tmpkeys.insert(it.key());
      }

      if (tmpkeys != jsonkeys)
      {
        ut::runtime_error("Invalid key(s) in array data");
      }
    }
  }

  data = json;
}

/* ------------------------------------------------------------------ */
