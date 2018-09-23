/*!
  @file src/pybind/processors/py_pro_radial_distribution_function_with_deformation.cpp
  @brief This file is for binding ProRadialDistributionFunctionWithDeformation class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_pro_radial_distribution_function_with_deformation.h"

void pybind::py_pro_radial_distribution_function_with_deformation(py::module &m)
{
  py::class_<ProRadialDistributionFunctionWithDeformation,PyProcessor<ProRDFWD>,ProRDF,Processor,ShPtr<ProRDFWD>>(m, "ProRadialDistributionFunctionWithDeformation")
    .def(py::init<const ElPtr &,const ElPtr &>())
    .def(py::init<const Vec<std::pair<ElPtr,ElPtr>> &>())
    .def("set_margin", &ProRDFWD::set_margin)
    .def("get_gyration_radius", &ProRDFWD::get_gyration_radius)
    .def("get_gyration_radius_traj",&ProRDFWD::get_gyration_radius_traj)
    .def(
      "get_squared_gyration_radius",
      &ProRDFWD::get_squared_gyration_radius)
    .def(
      "get_squared_gyration_radius_traj",
      &ProRDFWD::get_squared_gyration_radius_traj);
}
