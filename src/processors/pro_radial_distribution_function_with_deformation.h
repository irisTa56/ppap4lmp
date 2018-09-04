/* ---------------------------------------------------------------------
ProRadialDistributionFunctionWithDeformation: stands for Processor
which computes Radial Distribution Function (RDF) taking Deformation
into consideration; Deformation is guessed using gyration radius in
perpendicular and parallel directions of the point-to-point vector.

create: 2018/09/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H
#define PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H

#include <processors/pro_radial_distribution_function.h>

using ProRDF = ProRadialDistributionFunction;

class ProRadialDistributionFunctionWithDeformation : public ProRDF {
  double margin = 1.0;
 protected:
  virtual void run_impl(
    const int index) override;
 public:
  using ProRDF::ProRDF;
  virtual ~ProRadialDistributionFunctionWithDeformation() = default;
  void set_margin(
    double margin_);
};

using ProRDFWD = ProRadialDistributionFunctionWithDeformation;

#endif