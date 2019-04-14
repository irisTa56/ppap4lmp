/*!
  @file src/utils/runtime_error.cpp
  @brief This file has an implementation of ::utils::runtime_error.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#include <alias/pybind.h>

#include "runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void ut::runtime_error(
  const Str &msg)
{
  #pragma omp critical (raise)
  {
    PyErr_SetString(PyExc_RuntimeError, msg.c_str());
  }

  throw std::runtime_error(msg);
}
