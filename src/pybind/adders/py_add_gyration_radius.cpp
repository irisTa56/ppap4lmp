/*!
  @file src/pybind/adders/py_add_gyration_radius.cpp
  @brief This file is for binding AddGyrationRadius class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_add_gyration_radius.h"

void pybind::py_add_gyration_radius(py::module &m)
{
  py::class_<AddGyrationRadius,PyUpdater<AddGyrationRadius>,Adder,Updater,ShPtr<AddGyrationRadius>>(m, "AddGyrationRadius")
    .def(py::init<>())
    .def(
      "with_sqrted", &AddGyrationRadius::with_sqrted,
      py::arg("add_sqrted_") = true);
}
