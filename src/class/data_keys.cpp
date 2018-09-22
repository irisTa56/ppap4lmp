/*!
  @file src/class/data_keys.cpp
  @brief This file has an implementation of DataKeys class,
  which is owned by Element class.
  @author Takayuki Kobayashi
  @date 2018/09/09
*/

#include <algorithm>

#include "data_keys.h"
#include "../utils/join.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void DataKeys::clear()
{
  _keys.clear();
}

/* ------------------------------------------------------------------ */

void DataKeys::set(
  const Set<Str> &keys)
{
  _keys = keys;
}

/* ------------------------------------------------------------------ */

void DataKeys::add(
  const Json &key_)
{
  for (const Str &key : key_.is_array() ? key_ : Json::array({key_}))
  {
    _keys.insert(key);
  }
}

/* ------------------------------------------------------------------ */

void DataKeys::remove(
  const Json &key_)
{
  for (const Str &key : key_.is_array() ? key_ : Json::array({key_}))
  {
    _keys.erase(key);
  }
}

/* ------------------------------------------------------------------ */

void DataKeys::required(
  const Json &key_)
{
  Vec<Str> missings;

  for (const Str &key : key_.is_array() ? key_ : Json::array({key_}))
  {
    if (_keys.find(key) == _keys.end())
    {
      missings.push_back(key);
    }
  }

  if (!missings.empty())
  {
    std::sort(missings.begin(), missings.end());

    ut::runtime_error(
      "Missing key(s) '" + ut::join(missings, "', '") + "'");
  }
}

/* ------------------------------------------------------------------ */

bool DataKeys::optional(
  const Json &key_)
{
  for (const Str &key : key_.is_array() ? key_ : Json::array({key_}))
  {
    if (_keys.find(key) == _keys.end())
    {
      return false;
    }
  }

  return true;
}

/* ------------------------------------------------------------------ */

const Set<Str> &DataKeys::get()
{
  return _keys;
}

/* ------------------------------------------------------------------ */
