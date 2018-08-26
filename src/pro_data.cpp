/* ---------------------------------------------------------------------
ProData: stands for Processor which returns Data itself.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "pro_data.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

ProData::ProData(
  ShPtr<GenElement> elem)
{
  register_generator(elem);
}

/* ------------------------------------------------------------------ */

ProData::ProData(
  List<ShPtr<GenElement>> elems)
{
  register_generators(elems);
}

/* ------------------------------------------------------------------ */

void ProData::run_impl(
  int index)
{
  auto elem = generators[index]->get_element();
  auto &data = elem->get_data();

  if (selected_keys.empty())
  {
    results[index] = data;
  }
  else
  {
    check_keys(elem, selected_keys);

    Json json;

    if (data.is_array())
    {
      json = Json::array({});
      json.get_ref<Json::array_t&>().reserve(data.size());

      for (const auto &d : data)
      {
        Json tmp;

        for (const auto &k : selected_keys)
        {
          tmp[k] = d[k];
        }

        json.push_back(tmp);
      }
    }
    else
    {
      for (const auto &k : selected_keys)
      {
        json[k] = data[k];
      }
    }

    results[index] = json;
  }
}

/* ------------------------------------------------------------------ */

void ProData::prepare()
{
  results.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProData::select(
  py::args args)
{
  for (const auto &arg : args)
  {
    selected_keys.push_back(arg.cast<Str>());
  }
}

/* ------------------------------------------------------------------ */

const List<Json> &ProData::get_results()
{
  return results;
}
