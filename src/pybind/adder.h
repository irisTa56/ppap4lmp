#ifndef PYBIND_ADDER_H
#define PYBIND_ADDER_H

#include <adders/adder.h>
#include <pybind/updater.h>

static void pybind_adder(py::module &m)
{
  py::class_<
    Adder,PyUpdater<Adder>,Updater,ShPtr<Adder>>(m, "Adder")
    .def(py::init<>());
}

#endif