/*!
  @file src/pybind/starters/py_sta_dump_atoms.cpp
  @brief This file is for binding StaDumpAtoms class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_sta_dump_atoms.h"

void pybind::py_sta_dump_atoms(py::module &m)
{
  py::class_<StaDumpAtoms,PyUpdater<StaDumpAtoms>,StaDump,Starter,Updater,ShPtr<StaDumpAtoms>>(m, "StaDumpAtoms")
    .def(py::init<const Str &, const int>());
}
