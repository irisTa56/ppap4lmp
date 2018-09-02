#ifndef PYBIND_STA_BEADS_H
#define PYBIND_STA_BEADS_H

#include <starters/sta_beads.h>
#include <pybind/starter.h>

static void pybind_sta_beads(py::module &m)
{
  py::class_<StaBeads,PyUpdater<StaBeads>,Starter,Updater,ShPtr<StaBeads>>(m, "StaBeads")
    .def(py::init<ShPtr<Element>,const List<Json> &>())
    .def(py::init<ShPtr<Element>,const Dict<int,List<Json>> &>());
}

#endif