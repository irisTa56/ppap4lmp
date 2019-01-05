/*!
  @file src/pybind/adders/py_add_bond_angle.cpp
  @brief This file is for binding AddBondAngle class to Python.
  @author Yang Juntao
  @date 2018/12/20
*/

#include "py_add_bond_angle.h"

void pybind::py_add_bond_angle(py::module &m)
{
  py::class_<AddBondAngle,PyUpdater<AddBondAngle>,Adder,Updater,ShPtr<AddBondAngle>>(m, "AddBondAngle")
    .def(py::init<const ElPtr &>());
}
