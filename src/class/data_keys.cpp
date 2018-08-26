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
  const Str &key)
{
  _keys.insert(key);
}

/* ------------------------------------------------------------------ */

void DataKeys::add(
  const Set<Str> &keys)
{
  for (const auto &key : keys)
  {
    _keys.insert(key);
  }
}

/* ------------------------------------------------------------------ */

void DataKeys::add(
  const std::initializer_list<Str> &keys)
{
  add(Set<Str>(keys));
}

/* ------------------------------------------------------------------ */

void DataKeys::remove(
  const Str &key)
{
  _keys.erase(key);
}

/* ------------------------------------------------------------------ */

void DataKeys::remove(
  const Set<Str> &keys)
{
  for (const auto &key : keys)
  {
    _keys.erase(key);
  }
}

/* ------------------------------------------------------------------ */

void DataKeys::remove(
  const std::initializer_list<Str> &keys)
{
  remove(Set<Str>(keys));
}

/* ------------------------------------------------------------------ */

void DataKeys::required(
  const Str &key)
{
  if (_keys.find(key) == _keys.end())
  {
    ut::runtime_error("Missing key '" + key + "'");
  }
}

/* ------------------------------------------------------------------ */

void DataKeys::required(
  const Set<Str> &keys)
{
  Vec<Str> missings;

  for (const auto &key : keys)
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

void DataKeys::required(
  const std::initializer_list<Str> &keys)
{
  required(Set<Str>(keys));
}

/* ------------------------------------------------------------------ */

bool DataKeys::optional(
  const Str &key)
{
  return _keys.find(key) != _keys.end();
}

/* ------------------------------------------------------------------ */

bool DataKeys::optional(
  const Set<Str> &keys)
{
  for (const auto &key : keys)
  {
    if (_keys.find(key) == _keys.end())
    {
      return false;
    }
  }

  return true;
}

/* ------------------------------------------------------------------ */

bool DataKeys::optional(
  const std::initializer_list<Str> &keys)
{
  return optional(Set<Str>(keys));
}

/* ------------------------------------------------------------------ */

const Set<Str> &DataKeys::get()
{
  return _keys;
}

/* ------------------------------------------------------------------ */
