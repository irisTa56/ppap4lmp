/*!
  @file src/processors/pro_data.cpp
  @brief This file has an implementation of ProData class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/06/22
*/

#include <alias/pybind.h>

#include "pro_data.h"
#include "../utils/pyargs_to_vec.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

ProData::ProData(
  const ElPtr &elem)
{
  register_generator(elem);
}

/* ------------------------------------------------------------------ */

ProData::ProData(
  const Vec<ElPtr> &elems)
{
  register_generators(elems);
}

/* ------------------------------------------------------------------ */

void ProData::run_impl(
  const int index)
{
  auto elem = generators[index]->get_element();
  auto &data = elem->get_data();

  if (selected_keys.empty())
  {
    results[index] = data;
  }
  else
  {
    elem->check_required_keys(selected_keys);

    auto json = Json::array();

    if (data.is_array())
    {
      json.get_ref<Json::array_t&>().reserve(data.size());
    }

    for (const auto &d : data.is_array() ? data : Json::array({data}))
    {
      json.push_back({});
      auto &elem = json.back();

      for (const auto &k : selected_keys)
      {
        elem[k] = d[k];
      }
    }

    results[index].swap(data.is_array() ? json : json.front());
  }
}

/* ------------------------------------------------------------------ */

void ProData::prepare()
{
  results.clear();
  results.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProData::select(
  const py::args &args)
{
  ut::pyargs_to_vec(args, selected_keys);
}

/* ------------------------------------------------------------------ */

const Vec<Json> &ProData::get_results()
{
  return results;
}
