/*!
  @file src/pybind/adders/py_adder.cpp
  @brief This file is for binding Adder class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_adder.h"

void pybind::py_adder(py::module &m)
{
  py::class_<
    Adder,PyUpdater<Adder>,Updater,ShPtr<Adder>>(m, "Adder")
    .def(py::init<>());
}
