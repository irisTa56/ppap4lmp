/*!
  @file src/pybind/adders/py_add_wrapped_position.cpp
  @brief This file is for binding AddWrappedPosition class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_add_wrapped_position.h"

void pybind::py_add_wrapped_position(py::module &m)
{
  py::class_<AddWrappedPosition,PyUpdater<AddWrappedPosition>,Adder,Updater,ShPtr<AddWrappedPosition>>(m, "AddWrappedPosition")
    .def(py::init<const ElPtr &>());
}
