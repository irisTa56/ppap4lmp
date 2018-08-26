#ifndef PYBIND_STA_MOLECULES_H
#define PYBIND_STA_MOLECULES_H

#include <starters/sta_molecules.h>
#include <pybind/starters/starter.h>

static void pybind_sta_molecules(py::module &m)
{
  py::class_<StaMolecules,PyUpdater<StaMolecules>,Starter,Updater,ShPtr<StaMolecules>>(m, "StaMolecules")
    .def(py::init<const ShPtr<Element> &>());
}

#endif