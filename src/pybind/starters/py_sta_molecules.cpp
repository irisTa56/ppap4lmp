/*!
  @file src/pybind/starters/py_sta_molecules.cpp
  @brief This file is for binding StaMolecules class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_sta_molecules.h"

void pybind::py_sta_molecules(py::module &m)
{
  py::class_<StaMolecules,PyUpdater<StaMolecules>,Starter,Updater,ShPtr<StaMolecules>>(m, "StaMolecules")
    .def(py::init<const ElPtr &>());
}
