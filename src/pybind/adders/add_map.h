/*!
  @file src/pybind/adders/add_map.h
  @brief This file has a function to bind AddMap class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/26
*/

#ifndef PYBIND_ADD_MAP_H
#define PYBIND_ADD_MAP_H

#include <adders/add_map.h>
#include <pybind/adders/adder.h>

static void pybind_add_map(py::module &m)
{
  py::class_<AddMap,PyUpdater<AddMap>,Adder,Updater,ShPtr<AddMap>>(m, "AddMap")
    .def(py::init<const Str &,const Str &,const Map<Json,Json> &>())
    .def(
      "overwrite", &AddMap::overwrite,
      py::arg("do_overwrite_") = true);
}

#endif