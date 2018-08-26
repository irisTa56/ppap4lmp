#ifndef PYBIND_ADD_MOLECULAR_ORIENTATION_H
#define PYBIND_ADD_MOLECULAR_ORIENTATION_H

#include <adders/add_molecular_orientation.h>
#include <pybind/adders/adder.h>

static void pybind_add_molecular_orientation(py::module &m)
{
  py::class_<AddMolecularOrientation,PyUpdater<AddMolecularOrientation>,Adder,Updater,ShPtr<AddMolecularOrientation>>(m, "AddMolecularOrientation")
    .def(py::init<>());
}

#endif