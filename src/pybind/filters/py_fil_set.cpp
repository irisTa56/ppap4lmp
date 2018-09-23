/*!
  @file src/pybind/filters/py_fil_set.cpp
  @brief This file is for binding FilSet class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_fil_set.h"

void pybind::py_fil_set(py::module &m)
{
  py::class_<FilSet,PyUpdater<FilSet>,Filter,Updater,ShPtr<FilSet>>(m, "FilSet")
    .def(py::init<const Map<Str,Set<Json>> &>());
}
