/*!
  @file src/pybind/adders/add_inertia_moment.h
  @brief This file has a function to bind AddInertiaMoment class to
  Python.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

#ifndef PYBIND_ADD_INERTIA_MOMENT_H
#define PYBIND_ADD_INERTIA_MOMENT_H

#include <adders/add_inertia_moment.h>
#include <pybind/adders/adder.h>

static void pybind_add_inertia_moment(py::module &m)
{
  py::class_<AddInertiaMoment,PyUpdater<AddInertiaMoment>,Adder,Updater,ShPtr<AddInertiaMoment>>(m, "AddInertiaMoment")
    .def(py::init<const ElPtr &>());
}

#endif