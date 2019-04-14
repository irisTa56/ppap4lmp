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
    ut::runtime_error("No selected value(s) for ProValueArray");
  }

  auto elem = generators[index]->get_element();

  // NOTE: `id` property is check_required_keys to ensure data is sorted.
  elem->check_required_keys("id");

  elem->check_required_keys(selected_keys);

  auto &map_key_to_row = value_trajectories[index];

  auto &data = elem->get_data();

  auto row_length = data.is_array() ? data.size() : 1;

  for (const auto &key : selected_keys)
  {
    map_key_to_row[key].resize(row_length);
  }

  int irow = 0;

  for (const auto &d : data.is_array() ? data : Json::array({data}))
  {
    for (const auto &key : selected_keys)
    {
      map_key_to_row[key](irow) = d[key].get<double>();
    }

    irow++;
  }
}

/* ------------------------------------------------------------------ */

void ProValueArray::prepare()
{
  value_trajectories.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProValueArray::finish()
{
  auto front_key = selected_keys.front();

  auto row_length = value_trajectories.front()[front_key].size();

  for (const auto &trajectory : value_trajectories)
  {
    if (row_length != trajectory.at(front_key).size())
    {
      ut::runtime_error("Length of trajectories must be the same");
    }
  }

  for (const auto &key : selected_keys)
  {
    auto &array = results[key];
    array.resize(n_generators, row_length);

    int irow = 0;

    for (const auto &trajectory : value_trajectories)
    {
      array.row(irow++) = trajectory.at(key);
    }
  }

  value_trajectories.clear();
  value_trajectories.shrink_to_fit();
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
