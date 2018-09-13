/*!
  @file src/pybind/adders/add_rename.h
  @brief This file has a function to bind AddRename class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/17
*/

#ifndef PYBIND_ADD_RENAME_H
#define PYBIND_ADD_RENAME_H

#include <adders/add_rename.h>
#include <pybind/adders/adder.h>

static void pybind_add_rename(py::module &m)
{
  py::class_<AddRename,PyUpdater<AddRename>,Adder,Updater,ShPtr<AddRename>>(m, "AddRename")
    .def(py::init<const Str &,const Str &>())
    .def(
      "overwrite", &AddRename::overwrite,
      py::arg("do_overwrite_") = true);
}

#endif