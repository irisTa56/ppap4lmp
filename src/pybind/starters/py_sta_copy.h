#ifndef PYBIND_STA_COPY_H
#define PYBIND_STA_COPY_H

#include <starters/sta_copy.h>
#include <pybind/starters/py_starter.h>

static void pybind_sta_copy(py::module &m)
{
  py::class_<StaCopy,PyUpdater<StaCopy>,Starter,Updater,ShPtr<StaCopy>>(m, "StaCopy")
    .def(py::init<const ElPtr &>());
}

#endif