#ifndef PYBIND_PRO_THICKNESS_PROFILE_H
#define PYBIND_PRO_THICKNESS_PROFILE_H

#include <processors/pro_thickness_profile.h>
#include <pybind/processors_py/processor.h>

static void pybind_pro_thickness_profile(py::module &m)
{
  py::class_<ProThicknessProfile,PyProcessor<ProThicknessProfile>,Processor,ShPtr<ProThicknessProfile>>(m, "ProThicknessProfile")
    .def(py::init<const ElPtr &,const ElPtr &>())
    .def(py::init<const Vec<std::pair<ElPtr,ElPtr>> &>())
    .def("set_grid", &ProThicknessProfile::set_grid)
    .def("set_offset", &ProThicknessProfile::set_offset)
    .def(
      "shift_half_delta", &ProThicknessProfile::shift_half_delta,
      py::arg("shift_half_") = true)
    .def(
      "get_conditions", &ProThicknessProfile::get_conditions)
    .def(
      "get_profiles", &ProThicknessProfile::get_profiles);
}

#endif
