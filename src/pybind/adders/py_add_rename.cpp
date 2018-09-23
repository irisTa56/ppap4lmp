/*!
  @file src/pybind/adders/py_add_rename.cpp
  @brief This file is for binding AddRename class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_add_rename.h"

void pybind::py_add_rename(py::module &m)
{
  py::class_<AddRename,PyUpdater<AddRename>,Adder,Updater,ShPtr<AddRename>>(m, "AddRename")
    .def(py::init<const Str &,const Str &>())
    .def(
      "overwrite", &AddRename::overwrite,
      py::arg("do_overwrite_") = true);
}
