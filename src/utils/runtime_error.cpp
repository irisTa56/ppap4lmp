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

/* ------------------------------------------------------------------ */
