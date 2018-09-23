/*!
  @file src/pybind/starters/py_sta_copy.cpp
  @brief This file is for binding StaCopy class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_sta_copy.h"

void pybind::py_sta_copy(py::module &m)
{
  py::class_<StaCopy,PyUpdater<StaCopy>,Starter,Updater,ShPtr<StaCopy>>(m, "StaCopy")
    .def(py::init<const ElPtr &>());
}
