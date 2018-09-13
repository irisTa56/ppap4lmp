/*!
  @file src/pybind/adders/add_wrapped_position.h
  @brief This file has a function to bind AddWrappedPosition class to
  Python.
  @author Takayuki Kobayashi
  @date 2018/07/07
*/

#ifndef PYBIND_ADD_WRAPPED_POSITION_H
#define PYBIND_ADD_WRAPPED_POSITION_H

#include <adders/add_wrapped_position.h>
#include <pybind/adders/adder.h>

static void pybind_add_wrapped_position(py::module &m)
{
  py::class_<AddWrappedPosition,PyUpdater<AddWrappedPosition>,Adder,Updater,ShPtr<AddWrappedPosition>>(m, "AddWrappedPosition")
    .def(py::init<const ElPtr &>());
}

#endif