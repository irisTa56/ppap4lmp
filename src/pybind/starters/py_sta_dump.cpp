/*!
  @file src/pybind/starters/py_sta_dump.cpp
  @brief This file is for binding StaDump class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_sta_dump.h"

void pybind::py_sta_dump(py::module &m)
{
  py::class_<
    StaDump,PyUpdater<StaDump>,Starter,Updater,ShPtr<StaDump>>(m, "StaDump")
    .def(py::init<const Str &, int>());
}
