#ifndef PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H
#define PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H

#include <processors/pro_radial_distribution_function_with_deformation.h>
#include <pybind/py_processors/processor.h>

static void pybind_pro_radial_distribution_function_with_deformation(py::module &m)
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

#endif
