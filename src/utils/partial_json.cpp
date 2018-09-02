#include "partial_json.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

Json ut::partial_json(
  const Json &data,
  const Str &key)
{
  return ut::partial_json(data, {key});
}

/* ------------------------------------------------------------------ */

Json ut::partial_json(
  const Json &data,
  const Set<Str> &keys)
{
  Json tmp;

  if (data.is_array())
  {
    tmp = Json::array();
    tmp.get_ref<Json::array_t&>().reserve(data.size());

    for (const auto &d : data)
    {
      Json elem;

      for (const auto &k : keys)
      {
        elem[k] = d[k];
      }

      tmp.push_back(elem);
    }
  }
  else
  {
    for (const auto &k : keys)
    {
      tmp[k] = data[k];
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */
