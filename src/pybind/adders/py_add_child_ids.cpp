/*!
  @file src/pybind/adders/py_add_child_ids.cpp
  @brief This file is for binding AddChildIDs class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_add_child_ids.h"

void pybind::py_add_child_ids(py::module &m)
{
  py::class_<AddChildIDs,PyUpdater<AddChildIDs>,Adder,Updater,ShPtr<AddChildIDs>>(m, "AddChildIDs")
    .def(py::init<const ElPtr &,const Str &,const Str &>());
}
