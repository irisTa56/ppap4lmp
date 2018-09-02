#ifndef UTILS_PARTIAL_JSON_H
#define UTILS_PARTIAL_JSON_H

#include <alias/std.h>
#include <alias/json.h>

namespace utils
{
  Json partial_json(
    const Json &data,
    const Str &key);

  Json partial_json(
    const Json &data,
    const Set<Str> &keys);
}

#endif