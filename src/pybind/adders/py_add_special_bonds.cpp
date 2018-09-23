/*!
  @file src/pybind/adders/py_add_special_bonds.cpp
  @brief This file is for binding AddSpecialBonds class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_add_special_bonds.h"

void pybind::py_add_special_bonds(py::module &m)
{
  py::class_<AddSpecialBonds,PyUpdater<AddSpecialBonds>,Adder,Updater,ShPtr<AddSpecialBonds>>(m, "AddSpecialBonds")
    .def(py::init<const ElPtr &,const Vec<Vec<int>> &>())
    .def(py::init<const ElPtr &,const Map<int,Vec<Vec<int>>> &>());
}
