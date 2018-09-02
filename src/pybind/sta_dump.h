#ifndef PYBIND_STA_DUMP_H
#define PYBIND_STA_DUMP_H

#include <starters/sta_dump.h>
#include <pybind/starter.h>

static void pybind_sta_dump(py::module &m)
{
  py::class_<
    StaDump,PyUpdater<StaDump>,Starter,Updater,ShPtr<StaDump>>(m, "StaDump")
    .def(py::init<const Str &, int>());
}

#endif