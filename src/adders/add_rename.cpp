/*!
  @file src/adders/add_rename.cpp
  @brief This file has an implementation of AddRename class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/08/17
*/

#include "add_rename.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddRename::AddRename(
  const Str &key_old_,
  const Str &key_new_)
{
  key_old = key_old_;
  key_new = key_new_;
}

/* ------------------------------------------------------------------ */

void AddRename::compute_impl(
  Json &data,
  JsonToVoidFunc check_required_keys,
  JsonToBoolFunc check_optional_keys)
{
  check_required_keys(key_old);

  if (check_optional_keys(key_new) && !do_overwrite)
  {
    ut::runtime_error("Key '" + key_new + "' already exists");
  }

  if (data.is_array())
  {
    for (auto &d : data)
    {
      auto it = d.find(key_old);
      d[key_new] = *it;
      d.erase(it);
    }
  }
  else
  {
    auto it = data.find(key_old);
    data[key_new] = *it;
    data.erase(it);
  }
}

/* ------------------------------------------------------------------ */

ShPtr<AddRename> AddRename::overwrite(
  bool do_overwrite_)
{
  do_overwrite = do_overwrite_;

  return std::dynamic_pointer_cast<AddRename>(shared_from_this());
}
