/*!
  @file src/pybind/adders/py_add_dihedral_angle.cpp
  @brief This file is for binding AddDihedralAngle class to Python.
  @author Yang Juntao
  @date 2018/12/24
*/

#include "py_add_dihedral_angle.h"

void pybind::py_add_dihedral_angle(py::module &m)
{
  py::class_<AddDihedralAngle,PyUpdater<AddDihedralAngle>,Adder,Updater,ShPtr<AddDihedralAngle>>(m, "AddDihedralAngle")
    .def(py::init<const ElPtr &>());
}
