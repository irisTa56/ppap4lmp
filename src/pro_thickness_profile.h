/* ---------------------------------------------------------------------
ProThicknessProfile: stands for Processor which computes Thickness
Profile from positions.

create: 2018/07/08 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_THICKNESS_PROFILE_H
#define PRO_THICKNESS_PROFILE_H

#include "processor.h"

class ProThicknessProfile : public Processor {
  int nx = 1;
  int ny = 1;
  bool shift_half = false;
  double offset = 0.0;
  List<Json> conditions;
  List<ArrayXXd> profiles;
 protected:
  virtual void run_impl(int) override;
 public:
  ProThicknessProfile(ShPtr<GenElement>, ShPtr<GenElement>);
  ProThicknessProfile(
    List<std::pair<ShPtr<GenElement>,ShPtr<GenElement>>>);
  virtual ~ProThicknessProfile() = default;
  virtual void prepare() override;
  void set_grid(int, int);
  void set_offset(double);
  void shift_half_delta(bool shift_half_ = true);
  const List<Json> &get_conditions();
  const List<ArrayXXd> &get_profiles();
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_pro_thickness_profile(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ProThicknessProfile,PyProcessor<ProThicknessProfile>,Processor,ShPtr<ProThicknessProfile>>(m, "ProThicknessProfile")
    .def(py::init<ShPtr<GenElement>,ShPtr<GenElement>>())
    .def(py::init<List<std::pair<ShPtr<GenElement>,ShPtr<GenElement>>>>())
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
