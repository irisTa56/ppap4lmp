/*!
  @file src/pybind/adders/py_add_com_position.cpp
  @brief This file is for binding AddCoMPosition class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_add_com_position.h"

void pybind::py_add_com_position(py::module &m)
{
  py::class_<AddCoMPosition,PyUpdater<AddCoMPosition>,Adder,Updater,ShPtr<AddCoMPosition>>(m, "AddCoMPosition")
    .def(py::init<const ElPtr &>());
}
