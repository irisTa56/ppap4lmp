#ifndef PYBIND_ADD_INERTIA_MOMENT_H
#define PYBIND_ADD_INERTIA_MOMENT_H

#include <adders/add_inertia_moment.h>
#include <pybind/adder.h>

static void pybind_add_inertia_moment(py::module &m)
{
  py::class_<AddInertiaMoment,PyUpdater<AddInertiaMoment>,Adder,Updater,ShPtr<AddInertiaMoment>>(m, "AddInertiaMoment")
    .def(py::init<ShPtr<Element>>());
}

#endif