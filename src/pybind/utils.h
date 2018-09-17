/*!
  @file src/pybind/utils.h
  @brief This file is for binding utility functions to Python.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef PYBIND_UTILS_H
#define PYBIND_UTILS_H

#include <alias/pybind.h>
#include <utils/message.h>

/*!
  @brief Function to bind ::utils::log_switch to Python.
*/
static void pybind_utils(py::module &m)
{
  m.def("log_switch", &utils::log_switch);
}

#endif
