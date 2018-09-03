/* ---------------------------------------------------------------------
ProValueArray: stands for Processor returning selected (double) Values
contained in Arrays.

create: 2018/07/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

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

  elem->required("id");  // ensure data is sorted
  elem->required(selected_keys);

  auto size = data.is_array() ? data.size() : 1;

  Map<Str,RowArrayXd> rows;

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

  for (const auto &key : selected_keys)
  {
    results_trajs[key][index] = rows[key];
  }
}

/* ------------------------------------------------------------------ */

void ProValueArray::prepare()
{
  for (const auto &key : selected_keys)
  {
    results_trajs[key].resize(n_generators);
  }
}

/* ------------------------------------------------------------------ */

void ProValueArray::finish()
{
  auto &traj = results_trajs[selected_keys.front()];

  auto size = traj.front().size();

  for (const auto &tmp : traj)
  {
    if (size != tmp.size())
    {
      ut::runtime_error("Data sizes must be the same");
    }
  }

  for (const auto &item : results_trajs)
  {
    auto &array = results[item.first];
    array.resize(n_generators, size);

    int irow = 0;

    for (const auto &row : item.second)
    {
      array.row(irow++) = row;
    }
  }

  results_trajs.clear();
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
