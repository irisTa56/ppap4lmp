/*!
  @file src/pybind/adders/py_add_angle.cpp
  @brief This file is for binding AddAngle class to Python.
  @author Yang Juntao
  @date 2018/12/20
*/

#include "py_add_angle.h"

void pybind::py_add_angle(py::module &m)
{
  py::class_<AddAngle,PyUpdater<AddAngle>,Adder,Updater,ShPtr<AddAngle>>(m, "AddAngle")
    .def(py::init<const ElPtr &>());
}
