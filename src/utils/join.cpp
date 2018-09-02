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

    for (auto it = strs.begin()+1; it != strs.end(); ++it)
    {
      tmp += jointer + *it;
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */
