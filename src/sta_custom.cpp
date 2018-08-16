/* ---------------------------------------------------------------------
StaCustom: stands for Starter to generate Custom data.

create: 2018/08/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "sta_custom.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

StaCustom::StaCustom(const Json &json_)
{
  json = json_;

  auto front = json.is_array() ? json.front() : json;

  for (auto itr = front.begin(); itr != front.end(); ++itr)
  {
    jsonkeys.insert(itr.key());
  }

  if (json.is_array())
  {
    for (const auto &j : json)
    {
      Set<Str> tmpkeys;

      for (auto itr = j.begin(); itr != j.end(); ++itr)
      {
        tmpkeys.insert(itr.key());
      }

      if (tmpkeys != jsonkeys)
      {
        runtime_error("Invalid keys in array data");
      }
    }
  }
}

/* ------------------------------------------------------------------ */

void StaCustom::compute_impl(Json &data, Set<Str> &datakeys)
{
  data = json;
  datakeys = jsonkeys;
}