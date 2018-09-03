#ifndef PYBIND_PRO_THICKNESS_PROFILE_H
#define PYBIND_PRO_THICKNESS_PROFILE_H

#include <processors/pro_thickness_profile.h>
#include <pybind/processors/processor.h>

static void pybind_pro_thickness_profile(py::module &m)
{
  py::class_<ProThicknessProfile,PyProcessor<ProThicknessProfile>,Processor,ShPtr<ProThicknessProfile>>(m, "ProThicknessProfile")
    .def(py::init<const ShPtr<Element> &,const ShPtr<Element> &>())
    .def(py::init<const Vec<std::pair<ShPtr<Element>,ShPtr<Element>>> &>())
    .def("set_grid", &ProThicknessProfile::set_grid)
    .def("set_offset", &ProThicknessProfile::set_offset)
    .def(
      "shift_half_delta", &ProThicknessProfile::shift_half_delta,
      py::arg("shift_half_") = true)
    .def(
      "get_conditions", &ProThicknessProfile::get_conditions,
      py::return_value_policy::reference_internal)
    .def(
      "get_profiles", &ProThicknessProfile::get_profiles,
      py::return_value_policy::reference_internal);
}

#endif
