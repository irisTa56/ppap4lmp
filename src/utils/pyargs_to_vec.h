#ifndef PYARGS_TO_VEC_H
#define PYARGS_TO_VEC_H

#include <alias/std.h>
#include <alias/pybind.h>

namespace utils
{
  template<typename T>
  void pyargs_to_vec(
    const py::args &args,
    Vec<T> &vec);
}

#endif