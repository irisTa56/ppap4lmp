/*!
  @file src/pybind/adders/add_child_positions.h
  @brief This file has a function to bind AddChildPositions class to
  Python.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef PYBIND_ADD_CHILD_POSITIONS_H
#define PYBIND_ADD_CHILD_POSITIONS_H

#include <adders/add_child_positions.h>
#include <pybind/adders/adder.h>

static void pybind_add_child_positions(py::module &m)
{
  py::class_<AddChildPositions,PyUpdater<AddChildPositions>,Adder,Updater,ShPtr<AddChildPositions>>(m, "AddChildPositions")
    .def(py::init<const ElPtr &,const Str &>());
}

#endif