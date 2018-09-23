/*!
  @file src/pybind/adders/py_add_map.cpp
  @brief This file is for binding AddMap class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_add_map.h"

void pybind::py_add_map(py::module &m)
{
  py::class_<AddMap,PyUpdater<AddMap>,Adder,Updater,ShPtr<AddMap>>(m, "AddMap")
    .def(py::init<const Str &,const Str &,const Map<Json,Json> &>())
    .def(
      "overwrite", &AddMap::overwrite,
      py::arg("do_overwrite_") = true);
}
