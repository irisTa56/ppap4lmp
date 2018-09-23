/*!
  @file src/pybind/adders/py_add_child_positions.cpp
  @brief This file is for binding AddChildPositions class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_add_child_positions.h"

void pybind::py_add_child_positions(py::module &m)
{
  py::class_<AddChildPositions,PyUpdater<AddChildPositions>,Adder,Updater,ShPtr<AddChildPositions>>(m, "AddChildPositions")
    .def(py::init<const ElPtr &,const Str &>());
}
