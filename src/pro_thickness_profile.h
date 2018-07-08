/* ---------------------------------------------------------------------
ProThicknessProfile: stands for Processor which computes Thickness
Profile from positions of 'Atoms'.

create: 2018/07/08 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_THICKNESS_PROFILE_H
#define PRO_THICKNESS_PROFILE_H

#include "processor.h"

class ProThicknessProfile : public Processor {
  int nx;
  int ny;
  double offset = 0.0;
  std::vector<json> conditions;
  std::vector<Eigen::ArrayXXd> profiles;
 protected:
  virtual void run_impl(int) override;
  virtual void prepare_impl() override;
 public:
  ProThicknessProfile(std::shared_ptr<Generator>);
  ProThicknessProfile(std::vector<std::shared_ptr<Generator>>);
  virtual ~ProThicknessProfile() = default;
  void set_grid(int, int);
  void set_offset(double);
  const std::vector<json> &get_conditions();
  const std::vector<Eigen::ArrayXXd> &get_profiles();
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_pro_thickness_profile(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ProThicknessProfile,PyProcessor<ProThicknessProfile>,Processor,std::shared_ptr<ProThicknessProfile>>(m, "ProThicknessProfile")
    .def(py::init<std::shared_ptr<Generator>>())
    .def(py::init<std::vector<std::shared_ptr<Generator>>>())
    .def("set_grid", &ProThicknessProfile::set_grid)
    .def("set_offset", &ProThicknessProfile::set_offset)
    .def(
      "get_conditions", &ProThicknessProfile::get_conditions,
      py::return_value_policy::reference_internal)
    .def(
      "get_profiles", &ProThicknessProfile::get_profiles,
      py::return_value_policy::reference_internal);
}

#endif
