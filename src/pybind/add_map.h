#ifndef PYBIND_ADD_MAP_H
#define PYBIND_ADD_MAP_H

#include <adders/add_map.h>
#include <pybind/adder.h>

static void pybind_add_map(py::module &m)
{
  py::class_<AddMap,PyUpdater<AddMap>,Adder,Updater,ShPtr<AddMap>>(m, "AddMap")
    .def(py::init<const Str &,const Str &,const Dict<Json,Json> &>())
    .def(
      "overwrite", &AddMap::overwrite,
      py::arg("do_overwrite_") = true);
}

#endif