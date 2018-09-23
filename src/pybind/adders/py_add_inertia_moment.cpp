/*!
  @file src/pybind/adders/py_add_inertia_moment.cpp
  @brief This file is for binding AddInertiaMoment class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_add_inertia_moment.h"

void pybind::py_add_inertia_moment(py::module &m)
{
  py::class_<AddInertiaMoment,PyUpdater<AddInertiaMoment>,Adder,Updater,ShPtr<AddInertiaMoment>>(m, "AddInertiaMoment")
    .def(py::init<const ElPtr &>());
}
