/*!
  @file src/utils/pyargs_to_vec.cpp
  @brief This file has an implementation of ::utils::pyargs_to_vec.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#include "pyargs_to_vec.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

template<typename T>
void ut::pyargs_to_vec(
  const py::args &args,
  Vec<T> &vec)
{
  vec.clear();

  for (const auto &arg : args)
  {
    vec.push_back(arg.cast<T>());
  }
}

/* ------------------------------------------------------------------ */

/* NOTE:
  Template functions used by pybind11 must be instantiated.
*/

template void ut::pyargs_to_vec(
  const py::args &, Vec<Str> &);