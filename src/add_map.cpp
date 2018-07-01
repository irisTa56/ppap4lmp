/* ---------------------------------------------------------------------
AddMap: stands for Adder Mapping an existing property to a new property.

create: 2018/06/24 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_map.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddMap::AddMap(
  const std::string &key_ref_, const std::string &key_new_,
  JsonJson mapping_)
{
  key_ref = key_ref_;
  key_new = key_new_;
  mapping = mapping_;
}

/* ------------------------------------------------------------------ */

void AddMap::compute_impl(nlohmann::json &data)
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
