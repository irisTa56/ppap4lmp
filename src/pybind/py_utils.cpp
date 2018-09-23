/*!
  @file src/pybind/py_utils.cpp
  @brief This file is for binding utility functions to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_utils.h"

void pybind::py_utils(py::module &m)
{
  m.def("log_switch", &utils::log_switch);
}
