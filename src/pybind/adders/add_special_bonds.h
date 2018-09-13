/*!
  @file src/pybind/adders/add_special_bonds.h
  @brief This file has a function to bind AddSpecialBonds class to
  Python.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef PYBIND_ADD_SPECIAL_BONDS_H
#define PYBIND_ADD_SPECIAL_BONDS_H

#include <adders/add_special_bonds.h>
#include <pybind/adders/adder.h>

static void pybind_add_special_bonds(py::module &m)
{
  py::class_<AddSpecialBonds,PyUpdater<AddSpecialBonds>,Adder,Updater,ShPtr<AddSpecialBonds>>(m, "AddSpecialBonds")
    .def(py::init<const ElPtr &,const Vec<Vec<int>> &>())
    .def(py::init<const ElPtr &,const Map<int,Vec<Vec<int>>> &>());
}

#endif