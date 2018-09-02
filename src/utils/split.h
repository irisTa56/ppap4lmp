#ifndef UTILS_SPLIT_H
#define UTILS_SPLIT_H

#include <alias/std.h>

namespace utils
{
  Vec<Str> split(
    const Str &str,
    char delim = ' ');

  /* Not need for now
  Vec<Str> split2(
    const Str &str,
    char delim1 = ' ',
    char delim2 = ',');
  */
}

#endif