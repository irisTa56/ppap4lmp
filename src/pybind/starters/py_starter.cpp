/*!
  @file src/pybind/starters/py_starter.cpp
  @brief This file is for binding Starter class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_starter.h"

void pybind::py_starter(py::module &m)
{
  py::class_<
    Starter,PyUpdater<Starter>,Updater,ShPtr<Starter>>(m, "Starter")
    .def(py::init<>());
}
