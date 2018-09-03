/* ---------------------------------------------------------------------
ProThicknessProfile: stands for Processor which computes Thickness
Profile from positions.

create: 2018/07/08 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_THICKNESS_PROFILE_H
#define PRO_THICKNESS_PROFILE_H

#include <processors/processor.h>

class ProThicknessProfile : public Processor {
  int nx = 1;
  int ny = 1;
  bool shift_half = false;
  double offset = 0.0;
  Vec<Json> conditions;
  Vec<ArrayXXd> profiles;
 protected:
  virtual void run_impl(
    const int index) override;
 public:
  ProThicknessProfile(
    const ShPtr<Element> &atoms,
    const ShPtr<Element> &box);
  ProThicknessProfile(
    const Vec<std::pair<ShPtr<Element>,ShPtr<Element>>> &pairs);
  virtual ~ProThicknessProfile() = default;
  virtual void prepare() override;
  void set_grid(
    int nx_,
    int ny_);
  void set_offset(
    double offset_);
  void shift_half_delta(
    bool shift_half_ = true);
  const Vec<Json> &get_conditions();
  const Vec<ArrayXXd> &get_profiles();
};

#endif
