/* ---------------------------------------------------------------------
AddMap: stands for Adder for Mapping from existing properties to new
properties.

create: 2018/06/24 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_map.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddMap::AddMap(
  const std::string &key_ref_, const std::string &key_new_,
  const std::unordered_map<json,json> &mapping_)
{
  key_ref = key_ref_;
  key_new = key_new_;
  mapping = mapping_;
}

/* ------------------------------------------------------------------ */

void AddMap::compute_impl(json &data)
{
  if (data.is_array())
  {
    for (auto &d : data)
    {
      d[key_new] = mapping[d[key_ref]];
    }
  }
  else
  {
    data[key_new] = mapping[data[key_ref]];
  }
}
