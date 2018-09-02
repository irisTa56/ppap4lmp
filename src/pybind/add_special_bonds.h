#ifndef PYBIND_ADD_SPECIAL_BONDS_H
#define PYBIND_ADD_SPECIAL_BONDS_H

#include <adders/add_special_bonds.h>
#include <pybind/adder.h>

static void pybind_add_special_bonds(py::module &m)
{
  py::class_<AddSpecialBonds,PyUpdater<AddSpecialBonds>,Adder,Updater,ShPtr<AddSpecialBonds>>(m, "AddSpecialBonds")
    .def(py::init<ShPtr<GenElement>,const List<List<int>> &>())
    .def(py::init<ShPtr<GenElement>,const Dict<int,List<List<int>>> &>());
}

#endif