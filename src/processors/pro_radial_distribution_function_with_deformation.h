/* ---------------------------------------------------------------------
ProRadialDistributionFunctionWithDeformation: stands for Processor
which computes Radial Distribution Function (RDF) taking Deformation
into consideration; Deformation is guessed using gyration radius around
perpendicular and parallel directions of the point-to-point vector.

create: 2018/09/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H
#define PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H

#include <processors/processor.h>

class ProRadialDistributionFunctionWithDeformation : public Processor {
  int n_bins = 1;
  double bin_width = 1.0;
  double margin = 1.0;
  double gyration_radius = 0.0;
  bool bin_from_r = false;
  bool beyond_half = false;
  ArrayXd rdf;
  Vec<ArrayXd> rdf_traj;
  Vec<int> number_traj;
  Vec<double> volume_traj;
  Vec<ArrayXi> counts_traj;
 protected:
  virtual void run_impl(
    const int index) override;
 public:
  ProRadialDistributionFunctionWithDeformation(
    const ElPtr &beads,
    const ElPtr &box);
  ProRadialDistributionFunctionWithDeformation(
    const Vec<std::pair<ElPtr,ElPtr>> &pairs);
  virtual ~ProRadialDistributionFunctionWithDeformation() = default;
  virtual void prepare() override;
  virtual void finish() override;
  void set_bin(
    double bin_width_,
    int n_bins_);
  void set_margin(
    double margin_);
  void set_gyration_radius(
    double gyration_radius_);
  void bin_from_r_to_r_plus_dr(
    bool bin_from_r_ = true);
  void beyond_half_box_length(
    bool beyond_half_ = true);
  const ArrayXd get_r_axis();
  const ArrayXd &get_rdf();
  const Vec<ArrayXd> &get_rdf_traj();
};

using ProRDFWD = ProRadialDistributionFunctionWithDeformation;

#endif