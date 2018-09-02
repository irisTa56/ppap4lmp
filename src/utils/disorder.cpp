#include "disorder.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

template<typename T>
Set<T> ut::disorder(
  const Vec<T> &vec)
{
  return Set<T>(vec.begin(), vec.end());
}

/* ------------------------------------------------------------------ */

/* NOTE:
  Template functions used by pybind11 must be instantiated.
*/

template Set<Str> ut::disorder(
  const Vec<Str> &);
