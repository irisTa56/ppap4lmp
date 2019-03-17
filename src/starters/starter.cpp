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
  const ElPtr &elem,
  Json &data,
  const int dataid)
{
  if (check_blacklist(dataid))
  {
    if (data != nullptr)
    {
      ut::runtime_error("Starter accepts empty data only");
    }

    if (ext_generator)
    {
      Str myclassname
        = abi::__cxa_demangle(typeid(*this).name(), 0, 0, new int());

      ext_generator->set_checking_classname(myclassname);
    }

    compute_impl(data);

    elem->update_keys();

    if (data.is_array() && elem->optional_keys("id") && do_sorting_by_id)
    {
      sort_by_id(data);
    }
  }
}

/* ------------------------------------------------------------------ */
