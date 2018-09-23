/*!
  @file src/pybind/processors/py_pro_mean_square_displacement.cpp
  @brief This file is for binding ProMeanSquareDisplacement class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_pro_mean_square_displacement.h"

void pybind::py_pro_mean_square_displacement(py::module &m)
{
  py::class_<ProMeanSquareDisplacement,PyProcessor<ProMeanSquareDisplacement>,Processor,ShPtr<ProMeanSquareDisplacement>>(m, "ProMeanSquareDisplacement")
    .def(py::init<const Vec<ElPtr> &>())
    .def("set_dimension", &ProMeanSquareDisplacement::set_dimension)
    .def(
      "without_drift_correction", &ProMeanSquareDisplacement::without_drift_correction,
      py::arg("without_drift_correction_") = false)
    .def(
      "get_displacement2_array",
      &ProMeanSquareDisplacement::get_displacement2_array)
    .def(
      "get_mean_square_displacement",
      &ProMeanSquareDisplacement::get_mean_square_displacement);
}
