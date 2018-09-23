/*!
  @file src/pybind/py_updater.cpp
  @brief This file is for binding Updater class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_updater.h"

void pybind::py_updater(py::module &m)
{
  py::class_<
    Updater,PyUpdater<>,ShPtr<Updater>>(m, "Updater")
    .def(py::init<>());
}
