/*!
  @file src/starters/starter.cpp
  @brief This file has an implementation of Starter class,
  which is a subclass of Updater class.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#include "starter.h"
#include "../utils/map_to_index.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void Starter::sort_by_id(
  Json &data)
{
  auto map = ut::map_to_index(data, "id");
  auto vec = Vec<std::pair<int,int>>(map.begin(), map.end());

  std::sort(vec.begin(), vec.end());

  auto tmp = Json::array();
  tmp.get_ref<Json::array_t&>().reserve(vec.size());

  for (const auto &pair : vec)
  {
    tmp.push_back(data[pair.second]);
  }

  data.swap(tmp);
}

/* ------------------------------------------------------------------ */

void Starter::compute(
  Json &data,
  DataKeys &datakeys,
  const int dataid)
{
  if (check_blacklist(dataid))
  {
    if (data == nullptr)
    {
      compute_impl(data, datakeys);

      if (data.is_array() && datakeys.optional("id"))
      {
        sort_by_id(data);
      }
    }
    else
    {
      ut::runtime_error("Starter accepts empty data only");
    }
  }
}

/* ------------------------------------------------------------------ */
