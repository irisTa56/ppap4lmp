#ifndef PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_H
#define PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_H

#include <processors/pro_radial_distribution_function.h>
#include <pybind/processors/processor.h>

static void pybind_pro_radial_distribution_function(py::module &m)
{
  py::class_<ProRadialDistributionFunction,PyProcessor<ProRadialDistributionFunction>,Processor,ShPtr<ProRadialDistributionFunction>>(m, "ProRadialDistributionFunction")
    .def(py::init<const ShPtr<Element> &,const ShPtr<Element> &>())
    .def(py::init<const Vec<std::pair<ShPtr<Element>,ShPtr<Element>>> &>())
    .def("set_bin", &ProRadialDistributionFunction::set_bin)
    .def(
      "bin_from_r_to_r_plus_dr", &ProRadialDistributionFunction::bin_from_r_to_r_plus_dr,
      py::arg("bin_from_r_") = true)
    .def(
      "beyond_half_box_length", &ProRadialDistributionFunction::beyond_half_box_length,
      py::arg("beyond_half_") = true)
    .def("get_r_axis", &ProRadialDistributionFunction::get_r_axis)
    .def(
      "get_rdf", &ProRadialDistributionFunction::get_rdf,
      py::return_value_policy::reference_internal)
    .def(
      "get_rdf_traj", &ProRadialDistributionFunction::get_rdf_traj,
      py::return_value_policy::reference_internal);
}

#endif
