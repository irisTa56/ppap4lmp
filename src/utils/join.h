#ifndef UTILS_JOIN_H
#define UTILS_JOIN_H

#include <alias/std.h>

namespace utils
{
  Str join(
    const Vec<Str> &strs,
    const Str &jointer);
}

#endif