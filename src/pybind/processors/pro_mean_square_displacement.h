#ifndef PYBIND_PRO_MEAN_SQUARE_DISPLACEMENT_H
#define PYBIND_PRO_MEAN_SQUARE_DISPLACEMENT_H

#include <processors/pro_mean_square_displacement.h>
#include <pybind/processors/processor.h>

static void pybind_pro_mean_square_displacement(py::module &m)
{
  py::class_<ProMeanSquareDisplacement,PyProcessor<ProMeanSquareDisplacement>,Processor,ShPtr<ProMeanSquareDisplacement>>(m, "ProMeanSquareDisplacement")
    .def(py::init<const Vec<ElPtr> &>())
    .def("set_dimension", &ProMeanSquareDisplacement::set_dimension)
    .def(
      "without_drift_correction", &ProMeanSquareDisplacement::without_drift_correction,
      py::arg("without_drift_correction_") = false)
    .def(
      "get_displacement2_array", &ProMeanSquareDisplacement::get_displacement2_array,
      py::return_value_policy::reference_internal)
    .def(
      "get_mean_square_displacement", &ProMeanSquareDisplacement::get_mean_square_displacement,
      py::return_value_policy::reference_internal);
}

#endif
