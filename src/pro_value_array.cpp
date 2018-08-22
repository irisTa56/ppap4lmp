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
  register_generators(elem);
}

/* ------------------------------------------------------------------ */

ProValueArray::ProValueArray(
  List<ShPtr<GenElement>> elems)
{
  register_generators(elems);
}

/* ------------------------------------------------------------------ */

void ProValueArray::run_sort(
  int index,
  const Json &data)
{
  List<std::pair<int,Dict<Str,double>>> numbered_values;

  for (const auto &d : data.is_array() ? data : Json::array({data}))
  {
    Dict<Str,double> tmp;

    for (const auto &k : selected_keys)
    {
      auto &val = d[k];

      if (val.is_number_float())
      {
        tmp[k] = val;
      }
      else if (val.is_number())
      {
        message("ProValueArray: Converting an integer to float");
        tmp[k] = val;
      }
      else
      {
        runtime_error("ProValueArray: Value is not number");
      }
    }

    // value(s) is numbered by 'id'
    numbered_values.push_back(
      std::pair<int,Dict<Str,double>>(d["id"], tmp));
  }

  std::sort(
    numbered_values.begin(), numbered_values.end(),
    [](auto &a, auto &b)
    {
      return a.first < b.first;
    });

  auto size = numbered_values.size();

  for (const auto &k : selected_keys)
  {
    RowArrayXd row(size);

    for (int i = 0; i != size; ++i)
    {
      row(i) = numbered_values[i].second[k];
    }

    results_tmp[k][index] = row;
  }
}

/* ------------------------------------------------------------------ */

void ProValueArray::run_no_sort(
  int index,
  const Json &data)
{
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
      auto &val = d[k];

      if (val.is_number_float())
      {
        rows[k](irow) = val;
      }
      else if (val.is_number())
      {
        message("ProValueArray: Converting an integer to float");
        rows[k](irow) = val;
      }
      else
      {
        runtime_error("ProValueArray: Value is not number");
      }
    }

    irow++;
  }

  for (const auto &k : selected_keys)
  {
    results_tmp[k][index] = rows[k];
  }
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

  auto required_keys = selected_keys;
  required_keys.push_back("id");

  check_keys(elem, required_keys);

  if (do_sort)
  {
    run_sort(index, data);
  }
  else
  {
    run_no_sort(index, data);
  }
}

/* ------------------------------------------------------------------ */

void ProValueArray::prepare()
{
  for (const auto &k : selected_keys)
  {
    results_tmp[k].resize(n_generators);
  }
}

/* ------------------------------------------------------------------ */

void ProValueArray::finish()
{
  auto &list_of_row = results_tmp[selected_keys.front()];

  auto size = list_of_row.front().size();

  for (const auto &row : list_of_row)
  {
    if (size != row.size())
    {
      runtime_error("ProValueArray: Data sizes must be the same");
    }
  }

  for (const auto &item : results_tmp)
  {
    ArrayXXd arr(n_generators, size);

    for (int i = 0; i != n_generators; ++i)
    {
      arr.row(i) = item.second[i];
    }

    results[item.first] = arr;
  }
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

void ProValueArray::force_sort(
  bool do_sort_)
{
  do_sort = do_sort_;
}

/* ------------------------------------------------------------------ */

const Dict<Str,ArrayXXd> &ProValueArray::get_results()
{
  return results;
}
