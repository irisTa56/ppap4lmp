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
  auto &d = generators[index]->get_data();

  if (selected_keys.empty())
  {
    results[index] = d;
  }
  else
  {
    nlohmann::json j;

    if (d.is_array())
    {
      for (const auto &e : d)
      {
        nlohmann::json tmp;

        auto end = e.end();

        for (const auto &s : selected_keys)
        {
          auto val = e.find(s);

          if (val != end)
          {
            tmp[s] = *val;
          }
        }

        j.push_back(tmp);
      }
    }
    else
    {
      auto end = d.end();

      for (const auto &s : selected_keys)
      {
        auto val = d.find(s);

        if (val != end)
        {
          j[s] = *val;
        }
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

const std::vector<nlohmann::json> &ProData::get_results()
{
  return results;
}
