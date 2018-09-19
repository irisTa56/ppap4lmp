#ifndef PYBIND_STA_DUMP_ATOMS_H
#define PYBIND_STA_DUMP_ATOMS_H

#include <starters/sta_dump_atoms.h>
#include <pybind/starters/py_starter.h>

static void pybind_sta_dump_atoms(py::module &m)
{
  py::class_<StaDumpAtoms,PyUpdater<StaDumpAtoms>,StaDump,Starter,Updater,ShPtr<StaDumpAtoms>>(m, "StaDumpAtoms")
    .def(py::init<const Str &, const int>());
}

#endif