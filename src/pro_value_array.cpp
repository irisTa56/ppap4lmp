/* ---------------------------------------------------------------------
ProValueArray: stands for Processor returning selected (double) Values
contained in Arrays.

create: 2018/07/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <algorithm>

#include "pro_value_array.h"
#include "utils.h"

using NumberedVals
  = std::pair<int,std::unordered_map<std::string,double>>;

/* ------------------------------------------------------------------ */

void ProValueArray::finish()
{
  auto &vec_of_row = results_tmp[selected_keys.front()];

  int size = vec_of_row.front().size();

  for (const auto &row : vec_of_row)
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

void ProValueArray::select(py::args args)
{
  for (const auto &a : args)
  {
    selected_keys.push_back(a.cast<std::string>());
  }
}

/* ------------------------------------------------------------------ */

const ArrayXXdDict &ProValueArray::get_results()
{
  return results;
}

/* ------------------------------------------------------------------ */

void ProValueArray::run_impl(int index)
{
  if (selected_keys.empty())
  {
    message("ProValueArray: No selected values");
    return;
  }

  auto &data = generators[index]->get_data();

  auto required_keys = selected_keys;
  required_keys.push_back("id");

  if (!check_key(data, json(required_keys)))
  {
    runtime_error("ProValueArray: Required key(s) does not exist");
  }

  std::vector<NumberedVals> numbered_values;

  for (const auto &d : data.is_array() ? data : json({data}))
  {
    std::unordered_map<std::string,double> tmp;

    for (const auto &k : selected_keys)
    {
      auto &val = d[k];

      if (val.is_number())
      {
        tmp[k] = val;
      }
      else
      {
        runtime_error("ProValueArray: Value is not number");
      }
    }

    // value(s) is numbered by 'id'
    numbered_values.push_back(NumberedVals(d["id"], tmp));
  }

  std::sort(
    numbered_values.begin(), numbered_values.end(),
    [](auto &a, auto &b)
    {
      return a.first < b.first;
    });

  int size = numbered_values.size();

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

void ProValueArray::prepare_impl()
{
  for (const auto &k : selected_keys)
  {
    results_tmp[k].resize(n_generators);
  }
}
