#ifndef PYBIND_STARTER_H
#define PYBIND_STARTER_H

#include <starters/starter.h>
#include <pybind/py_updater.h>

static void pybind_starter(py::module &m)
{
  py::class_<
    Starter,PyUpdater<Starter>,Updater,ShPtr<Starter>>(m, "Starter")
    .def(py::init<>());
}

#endif