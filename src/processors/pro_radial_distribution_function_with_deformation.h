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
  ArrayXd Rg2_array;
  ArrayXd Rg2_para_array;  // parallel
  ArrayXd Rg2_perp_array;  // perpendicular
  Vec<ArrayXd> Rg2_array_traj;
  Vec<ArrayXd> Rg2_para_array_traj;
  Vec<ArrayXd> Rg2_perp_array_traj;
  Vec<ArrayXi> raw_counts_traj;
  Vec<ArrayXd> Rg2_sum_traj;
  Vec<ArrayXd> Rg2_para_sum_traj;
  Vec<ArrayXd> Rg2_perp_sum_traj;
 protected:
  virtual void run_impl(
    const int index) override;
 public:
  using ProRDF::ProRDF;
  virtual ~ProRadialDistributionFunctionWithDeformation() = default;
  virtual void prepare() override;
  virtual void finish() override;
  void set_margin(
    double margin_);
  Map<Str,ArrayXd> get_gyration_radius();
  Map<Str,Vec<ArrayXd>> get_gyration_radius_traj();
  Map<Str,ArrayXd> get_squared_gyration_radius();
  Map<Str,Vec<ArrayXd>> get_squared_gyration_radius_traj();
};

using ProRDFWD = ProRadialDistributionFunctionWithDeformation;

#endif