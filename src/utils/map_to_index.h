#ifndef UTILS_MAP_TO_INDEX_H
#define UTILS_MAP_TO_INDEX_H

#include <alias/std.h>
#include <alias/json.h>

namespace utils
{
  Map<Json,int> map_to_index(
    const Json &data,
    const Str &key);

  /* Not need for now
  Map<Json,int> map_to_index(
    const Json &data,
    const Vec<Str> &keys);
  */
}

#endif