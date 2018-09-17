/*!
  @file src/utils/map_to_index.cpp
  @brief This file has an implementation of ::utils::map_to_index.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#include "map_to_index.h"
#include "runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

Map<Json,int> ut::map_to_index(
  const Json &data,
  const Str &key)
{
  Map<Json,int> tmp;

  if (data.is_array())
  {
    tmp.reserve(data.size());

    int index = 0;

    for (const auto &d : data)
    {
      tmp[d[key]] = index++;
    }
  }

  if (tmp.size() != data.size())
  {
    ut::runtime_error("Map to index is not bijection");
  }

  return tmp;
}

/* ------------------------------------------------------------------ */
/* Not need for now
Map<Json,int> ut::map_to_index(
  const Json &data,
  const Vec<Str> &keys)
{
  Map<Json,int> tmp;

  if (data.is_array())
  {
    tmp.reserve(data.size());

    int index = 0;

    for (const auto &d : data)
    {
      auto array = Json::array();

      for (const auto &key : keys)
      {
        array.push_back(d[key]);
      }

      tmp[array] = index++;
    }
  }

  if (tmp.size() != data.size())
  {
    ut::runtime_error("Map to index is not bijection");
  }

  return tmp;
}

/* ------------------------------------------------------------------ */
