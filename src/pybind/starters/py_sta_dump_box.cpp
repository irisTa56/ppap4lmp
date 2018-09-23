/*!
  @file src/pybind/starters/py_sta_dump_box.cpp
  @brief This file is for binding StaDumpBox class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_sta_dump_box.h"

void pybind::py_sta_dump_box(py::module &m)
{
  py::class_<StaDumpBox,PyUpdater<StaDumpBox>,StaDump,Starter,Updater,ShPtr<StaDumpBox>>(m, "StaDumpBox")
    .def(py::init<const Str &, int>());
}
