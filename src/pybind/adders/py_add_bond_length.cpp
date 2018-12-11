/*!
  @file src/pybind/adders/py_add_bond_length.cpp
  @brief This file is for binding AddBondLength class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_add_bond_length.h"

void pybind::py_add_bond_length(py::module &m)
{
  py::class_<AddBondLength,PyUpdater<AddBondLength>,Adder,Updater,ShPtr<AddBondLength>>(m, "AddBondLength")
    .def(py::init<const ElPtr &>());
}
