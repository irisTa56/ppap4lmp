/* ---------------------------------------------------------------------
ProValueArray: stands for Processor returning selected (double) Values
contained in Arrays.

create: 2018/07/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "pro_value_array.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

ProValueArray::ProValueArray(ShPtr<GenElement> elem)
{
  register_generators(elem);
}

/* ------------------------------------------------------------------ */

ProValueArray::ProValueArray(List<ShPtr<GenElement>> elems)
{
  register_generators(elems);
}

/* ------------------------------------------------------------------ */

void ProValueArray::run_impl(int index)
{
  if (selected_keys.empty())
  {
    runtime_error("ProValueArray: No selected values");
    return;
  }

  auto elem = generators[index]->get_element();
  auto &data = elem->get_data();

  auto required_keys = selected_keys;
  required_keys.insert("id");

  if (!check_containment<Str>(elem->get_keys(), required_keys))
  {
    runtime_error(
      "ProValueArray: Selected key(s) and 'id' do not exist");
    return;
  }

  List<std::pair<int,Dict<Str,double>>> numbered_values;

  for (const auto &d : data.is_array() ? data : Json({data}))
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
      }
      else
      {
        runtime_error("ProValueArray: Value is not number");
        return;
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
  auto &vec_of_row = results_tmp[*(selected_keys.begin())];

  int size = vec_of_row.front().size();

  for (const auto &row : vec_of_row)
  {
    if (size != row.size())
    {
      runtime_error("ProValueArray: Data sizes must be the same");
      return;
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
    selected_keys.insert(a.cast<Str>());
  }
}

/* ------------------------------------------------------------------ */

const Dict<Str,ArrayXXd> &ProValueArray::get_results()
{
  return results;
}
