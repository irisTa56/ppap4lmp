/*!
  @file src/pybind/adders/py_add_molecular_orientation.cpp
  @brief This file is for binding AddMolecularOrientation class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_add_molecular_orientation.h"

void pybind::py_add_molecular_orientation(py::module &m)
{
  py::class_<AddMolecularOrientation,PyUpdater<AddMolecularOrientation>,Adder,Updater,ShPtr<AddMolecularOrientation>>(m, "AddMolecularOrientation")
    .def(py::init<>());
}
