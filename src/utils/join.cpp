/*!
  @file src/utils/join.cpp
  @brief This file has an implementation of ::utils::join.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#include "join.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

Str ut::join(
  const Vec<Str> &strs,
  const Str &jointer)
{
  Str tmp;

  if (!strs.empty())
  {
    tmp = strs.front();

    for (auto it = strs.cbegin()+1; it != strs.cend(); ++it)
    {
      tmp += jointer + *it;
    }
  }

  return tmp;
}
