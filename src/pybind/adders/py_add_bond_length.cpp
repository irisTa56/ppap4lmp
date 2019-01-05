/*!
  @file src/pybind/adders/py_add_bond_length.cpp
  @brief This file is for binding AddBondLength class to Python.
  @author Yang Juntao & Kawai Kento
  @date 2018/12/06
*/

#include "py_add_bond_length.h"

void pybind::py_add_bond_length(py::module &m)
{
  py::class_<AddBondLength,PyUpdater<AddBondLength>,Adder,Updater,ShPtr<AddBondLength>>(m, "AddBondLength")
    .def(py::init<const ElPtr &>());
}
