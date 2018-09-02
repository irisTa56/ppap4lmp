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
  List<Json> conditions;
  List<ArrayXXd> profiles;
 protected:
  virtual void run_impl(
    int index) override;
 public:
  ProThicknessProfile(
    ShPtr<GenElement> atoms,
    ShPtr<GenElement> box);
  ProThicknessProfile(
    List<std::pair<ShPtr<GenElement>,ShPtr<GenElement>>> pairs);
  virtual ~ProThicknessProfile() = default;
  virtual void prepare() override;
  void set_grid(
    int nx_,
    int ny_);
  void set_offset(
    double offset_);
  void shift_half_delta(
    bool shift_half_ = true);
  const List<Json> &get_conditions();
  const List<ArrayXXd> &get_profiles();
};

#endif
