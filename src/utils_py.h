#ifndef UTILS_PY_H
#define UTILS_PY_H

#include "utils.h"

extern bool ToF_LOGGING;

/* ------------------------------------------------------------------ */

static void log_switch(bool input)
{
  ToF_LOGGING = input;
}

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_utils(py::module &m)
{
  m.def("log_switch", &log_switch);
}

#endif
