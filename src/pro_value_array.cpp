/* ---------------------------------------------------------------------
ProValueArray: stands for Processor returning selected (double) Values
contained in Arrays.

create: 2018/07/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "pro_value_array.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

ProValueArray::ProValueArray(
  ShPtr<GenElement> elem)
{
  register_generator(elem);
}

/* ------------------------------------------------------------------ */

ProValueArray::ProValueArray(
  List<ShPtr<GenElement>> elems)
{
  register_generators(elems);
}

/* ------------------------------------------------------------------ */

void ProValueArray::run_impl(
  int index)
{
  if (selected_keys.empty())
  {
    runtime_error("ProValueArray: No selected values");
  }

  auto elem = generators[index]->get_element();
  auto &data = elem->get_data();

  check_key(elem, "id");
  check_keys(elem, selected_keys);

  auto size = data.is_array() ? data.size() : 1;

  Dict<Str,RowArrayXd> rows;

  for (const auto &k : selected_keys)
  {
    rows[k] = RowArrayXd(size);
  }

  int irow = 0;

  for (const auto &d : data.is_array() ? data : Json::array({data}))
  {
    for (const auto &k : selected_keys)
    {
      rows[k](irow) = d[k].get<double>();
    }

    irow++;
  }

  for (const auto &k : selected_keys)
  {
    results_trajs[k][index] = rows[k];
  }
}

/* ------------------------------------------------------------------ */

void ProValueArray::prepare()
{
  for (const auto &k : selected_keys)
  {
    results_trajs[k].resize(n_generators);
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
      runtime_error("ProValueArray: Data sizes must be the same");
    }
  }

  for (const auto &item : results_trajs)
  {
    ArrayXXd arr(n_generators, size);

    for (int i = 0; i != n_generators; ++i)
    {
      arr.row(i) = item.second[i];
    }

    results[item.first] = arr;
  }

  results_trajs.clear();
}

/* ------------------------------------------------------------------ */

void ProValueArray::select(
  py::args args)
{
  for (const auto &a : args)
  {
    selected_keys.push_back(a.cast<Str>());
  }
}

/* ------------------------------------------------------------------ */

const Dict<Str,ArrayXXd> &ProValueArray::get_results()
{
  return results;
}
