/* ---------------------------------------------------------------------
StaCustom: stands for Starter to generate Custom data.

create: 2018/08/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "sta_custom.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

StaCustom::StaCustom(
  const Json &json_)
{
  json = json_;

  auto front = json.is_array() ? json.front() : json;

  for (auto it = front.begin(); it != front.end(); ++it)
  {
    jsonkeys.insert(it.key());
  }
}

/* ------------------------------------------------------------------ */

void StaCustom::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
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
  datakeys.set(jsonkeys);
}