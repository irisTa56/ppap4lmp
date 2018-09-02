#ifndef PYBIND_UTILS_H
#define PYBIND_UTILS_H

#include <alias/pybind.h>
#include <utils/message.h>

static void pybind_utils(py::module &m)
{
  m.def("log_switch", &utils::log_switch);
}

#endif
