/* ---------------------------------------------------------------------
Starter: is an abstract class to parse data from a file or other data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "starter.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void Starter::sort_by_id(
  Json &data)
{
  auto dict = get_map_to_index(data, "id");
  auto list = List<std::pair<int,int>>(dict.begin(), dict.end());

  std::sort(list.begin(), list.end());

  auto tmp = Json::array();
  tmp.get_ref<Json::array_t&>().reserve(list.size());

  for (const auto &pair : list)
  {
    tmp.push_back(data[pair.second]);
  }

  data.swap(tmp);
}

/* ------------------------------------------------------------------ */

void Starter::compute(
  Json &data,
  Set<Str> &datakeys,
  int dataid)
{
  if (check_blacklist(dataid))
  {
    if (data == nullptr)
    {
      compute_impl(data, datakeys);

      if (data.is_array() && check_containment<Str>(datakeys, "id"))
      {
        sort_by_id(data);
      }
    }
    else
    {
      runtime_error("Starter accepts empty data only");
    }
  }
}
