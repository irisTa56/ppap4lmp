/*!
  @file src/processors/pro_value_array.cpp
  @brief This file has an implementation of ProValueArray class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/07/16
*/

#include <functional>
#include <alias/pybind.h>

#include "pro_value_array.h"
#include "../utils/runtime_error.h"
#include "../utils/pyargs_to_vec.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

ProValueArray::ProValueArray(
  const ElPtr &elem)
{
  register_generator(elem);
}

/* ------------------------------------------------------------------ */

ProValueArray::ProValueArray(
  const Vec<ElPtr> &elems)
{
  register_generators(elems);
}

/* ------------------------------------------------------------------ */

void ProValueArray::run_impl(
  const int index)
{
  if (selected_keys.empty())
  {
    ut::runtime_error("Selected value(s) for ProValueArray");
  }

  auto elem = generators[index]->get_element();
  auto &data = elem->get_data();

  // NOTE: `id` property is required to ensure data is sorted.
  elem->required("id");
  elem->required(selected_keys);

  auto &rows = results_trajs[index];

  auto size = data.is_array() ? data.size() : 1;

  for (const auto &key : selected_keys)
  {
    rows[key].resize(size);
  }

  int irow = 0;

  for (const auto &d : data.is_array() ? data : Json::array({data}))
  {
    for (const auto &key : selected_keys)
    {
      rows[key](irow) = d[key].get<double>();
    }

    irow++;
  }
}

/* ------------------------------------------------------------------ */

void ProValueArray::prepare()
{
  results_trajs.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProValueArray::finish()
{
  auto front_key = selected_keys.front();

  auto size = results_trajs.front()[front_key].size();

  for (const auto &tmp : results_trajs)
  {
    if (size != tmp.at(front_key).size())
    {
      ut::runtime_error("Data sizes must be the same");
    }
  }

  for (const auto &key : selected_keys)
  {
    auto &array = results[key];
    array.resize(n_generators, size);

    int irow = 0;

    for (const auto &tmp : results_trajs)
    {
      array.row(irow++) = tmp.at(key);
    }
  }

  results_trajs.clear();
  results_trajs.shrink_to_fit();
}

/* ------------------------------------------------------------------ */

void ProValueArray::select(
  const py::args &args)
{
  ut::pyargs_to_vec(args, selected_keys);
}

/* ------------------------------------------------------------------ */

const Map<Str,ArrayXXd> &ProValueArray::get_results()
{
  return results;
}

/* ------------------------------------------------------------------ */
