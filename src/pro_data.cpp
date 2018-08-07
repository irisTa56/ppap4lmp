/* ---------------------------------------------------------------------
ProData: stands for Processor which returns Data itself.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "pro_data.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void ProData::select(py::args args)
{
  for (const auto &a : args)
  {
    selected_keys.push_back(a.cast<std::string>());
  }
}

/* ------------------------------------------------------------------ */

void ProData::run_impl(int index)
{
  auto &data = generators[index]->get_data();

  if (selected_keys.empty())
  {
    results[index] = data;
  }
  else
  {
    if (!check_key(data, json(selected_keys)))
    {
      runtime_error("ProData: Selected key(s) does not exist");
    }

    json j;

    if (data.is_array())
    {
      for (const auto &d : data)
      {
        json tmp;

        for (const auto &k : selected_keys)
        {
          tmp[k] = d[k];
        }

        j.push_back(tmp);
      }
    }
    else
    {
      for (const auto &k : selected_keys)
      {
        j[k] = data[k];
      }
    }

    results[index] = j;
  }
}

/* ------------------------------------------------------------------ */

void ProData::prepare_impl()
{
  results.resize(n_generators);
}

/* ------------------------------------------------------------------ */

const std::vector<json> &ProData::get_results()
{
  return results;
}
