/*!
  @file src/pybind/starters/py_sta_beads.cpp
  @brief This file is for binding StaBeads class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_sta_beads.h"

void pybind::py_sta_beads(py::module &m)
{
  py::class_<StaBeads,PyUpdater<StaBeads>,Starter,Updater,ShPtr<StaBeads>>(m, "StaBeads")
    .def(py::init<const ElPtr &,const Vec<Json> &>())
    .def(py::init<const ElPtr &,const Map<int,Vec<Json>> &>());
}
