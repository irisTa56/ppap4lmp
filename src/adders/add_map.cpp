/*!
  @file src/adders/add_map.cpp
  @brief This file has an implementation of AddMap class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/06/24
*/

#include "add_map.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddMap::AddMap(
  const Str &key_ref_,
  const Str &key_new_,
  const Map<Json,Json> &mapping_)
{
  key_ref = key_ref_;
  key_new = key_new_;
  mapping = mapping_;
}

/* ------------------------------------------------------------------ */

void AddMap::compute_impl(
  Json &data)
{
  check_required_keys(key_ref);

  if (check_optional_keys(key_new) && !do_overwrite)
  {
    ut::runtime_error("Key '" + key_new + "' already exists");
  }

  if (data.is_array())
  {
    for (auto &d : data)
    {
      d[key_new] = mapping.at(d[key_ref]);
    }
  }
  else
  {
    data[key_new] = mapping.at(data[key_ref]);
  }
}

/* ------------------------------------------------------------------ */

ShPtr<AddMap> AddMap::overwrite(
  bool do_overwrite_)
{
  do_overwrite = do_overwrite_;

  return std::dynamic_pointer_cast<AddMap>(shared_from_this());
}

/* ------------------------------------------------------------------ */
