#pragma once

#include "pro_radial_distribution_function.h"

class ProRadialDistributionFunctionByType
  : public ProRadialDistributionFunction
{
public:
  using ProRadialDistributionFunction::ProRadialDistributionFunction;

  void set_target_type(int type);

protected:
  void run_impl(const int index) override;

private:
  int target_type = -1;
};
