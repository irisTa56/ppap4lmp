#ifndef PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H
#define PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H

#include <processors/pro_radial_distribution_function_with_deformation.h>
#include <pybind/processors/processor.h>

static void pybind_pro_radial_distribution_function_with_deformation(py::module &m)
{
  py::class_<ProRDFWD,PyProcessor<ProRDFWD>,Processor,ShPtr<ProRDFWD>>(m, "ProRDFWD")
    .def(py::init<const ElPtr &,const ElPtr &>())
    .def(py::init<const Vec<std::pair<ElPtr,ElPtr>> &>())
    .def("set_bin", &ProRDFWD::set_bin)
    .def("set_margin", &ProRDFWD::set_margin)
    .def("set_gyration_radius", &ProRDFWD::set_gyration_radius)
    .def(
      "bin_from_r_to_r_plus_dr", &ProRDFWD::bin_from_r_to_r_plus_dr,
      py::arg("bin_from_r_") = true)
    .def(
      "beyond_half_box_length", &ProRDFWD::beyond_half_box_length,
      py::arg("beyond_half_") = true)
    .def("get_r_axis", &ProRDFWD::get_r_axis)
    .def(
      "get_rdf", &ProRDFWD::get_rdf,
      py::return_value_policy::reference_internal)
    .def(
      "get_rdf_traj", &ProRDFWD::get_rdf_traj,
      py::return_value_policy::reference_internal);
}

#endif
