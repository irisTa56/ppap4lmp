/*!
  @file src/pybind/adders/add_gyration_radius.h
  @brief This file has a function to bind AddGyrationRadius class to
  Python.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

#ifndef PYBIND_ADD_GYRATION_RADIUS_H
#define PYBIND_ADD_GYRATION_RADIUS_H

#include <adders/add_gyration_radius.h>
#include <pybind/adders/adder.h>

static void pybind_add_gyration_radius(py::module &m)
{
  py::class_<AddGyrationRadius,PyUpdater<AddGyrationRadius>,Adder,Updater,ShPtr<AddGyrationRadius>>(m, "AddGyrationRadius")
    .def(py::init<>())
    .def(
      "with_squared", &AddGyrationRadius::with_squared,
      py::arg("add_squared_") = true)
    .def(
      "without_sqrted", &AddGyrationRadius::without_sqrted,
      py::arg("without_sqrted_") = true);
}

#endif