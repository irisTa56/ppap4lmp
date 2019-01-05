/*!
  @file src/utils/pyargs_to_vec.h
  @brief This file has a definition of ::utils::pyargs_to_vec.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef PYARGS_TO_VEC_H
#define PYARGS_TO_VEC_H

#include <alias/std.h>
#include <alias/pybind.h>

//! Namespace for utility functions.
namespace utils
{
  /*!
    @brief Convert a py::args (a variable number arguments) object
    to a ::Vec object.

    @param args
      Python's variable number arguments.

    @param vec
      Mutable reference to a ::Vec object where elements of the
      `args` are appended to.

    @return None.
  */
  template<typename T>
  void pyargs_to_vec(
    const py::args &args,
    Vec<T> &vec);
}

#endif