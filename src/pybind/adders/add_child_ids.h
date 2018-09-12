/*!
  @file src/pybind/adders/add_child_ids.h
  @brief This file has a function to bind AddChildIDs class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef PYBIND_ADD_CHILD_IDS_H
#define PYBIND_ADD_CHILD_IDS_H

#include <adders/add_child_ids.h>
#include <pybind/adders/adder.h>

static void pybind_add_child_ids(py::module &m)
{
  py::class_<AddChildIDs,PyUpdater<AddChildIDs>,Adder,Updater,ShPtr<AddChildIDs>>(m, "AddChildIDs")
    .def(py::init<const ElPtr &,const Str &,const Str &>());
}

#endif