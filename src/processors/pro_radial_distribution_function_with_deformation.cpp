/* ---------------------------------------------------------------------
ProRadialDistributionFunctionWithDeformation: stands for Processor
which computes Radial Distribution Function (RDF) taking Deformation
into consideration; Deformation is guessed using gyration radius in
perpendicular and parallel directions of the point-to-point vector.

create: 2018/09/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#define _USE_MATH_DEFINES

#include <cmath>

#include "pro_radial_distribution_function_with_deformation.h"
#include "../utils/message.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */
/*
ProRadialDistributionFunctionWithDeformation::ProRadialDistributionFunctionWithDeformation(
  const ElPtr &beads,
  const ElPtr &box)
{
  register_generator(ShPtr<GenDict>(
    new GenDict({{"Beads", beads}, {"Box", box}})));
}

/* ------------------------------------------------------------------ */
/*
ProRadialDistributionFunctionWithDeformation::ProRadialDistributionFunctionWithDeformation(
  const Vec<std::pair<ElPtr,ElPtr>> &pairs)
{
  Vec<ShPtr<GenDict>> gens;

  for (const auto &pair : pairs)
  {
    gens.push_back(ShPtr<GenDict>(
      new GenDict({{"Beads", pair.first}, {"Box", pair.second}})));
  }

  register_generators(gens);
}

/* ------------------------------------------------------------------ */

void ProRDFWD::run_impl(
  const int index)
{
  auto el_beads = generators[index]->get_element("Beads");

  el_beads->required({
    "I_xx", "I_yy", "I_zz", "I_xy", "I_yz", "I_zx", "mass",
    "x", "y", "z", "id"});

  auto &beads = el_beads->get_data();

  bool special_bonds_exist = el_beads->optional("special-bonds");

  auto el_box = generators[index]->get_element("Box");

  el_box->required({"lo_x", "lo_y", "lo_z", "hi_x", "hi_y", "hi_z"});

  auto &box = el_box->get_data();

  // preparation

  auto n_beads = beads.size();

  Vec<std::pair<VectorXd,MatrixXd>> rs_and_Is_per_mass;
  rs_and_Is_per_mass.reserve(n_beads);

  for (const auto &bead : beads)
  {
    rs_and_Is_per_mass.push_back(std::make_pair(
      (Eigen::Vector3d() << bead["x"], bead["y"], bead["z"])
      .finished(),
      (Eigen::Matrix3d() << bead["I_xx"], bead["I_xy"], bead["I_zx"],
                            bead["I_xy"], bead["I_yy"], bead["I_yz"],
                            bead["I_zx"], bead["I_yz"], bead["I_zz"])
      .finished() / bead["mass"].get<double>()));
  }

  ArrayXd length(3);
  length << box["hi_x"].get<double>() - box["lo_x"].get<double>(),
            box["hi_y"].get<double>() - box["lo_y"].get<double>(),
            box["hi_z"].get<double>() - box["lo_z"].get<double>();

  ArrayXd limits = beyond_half ? length : 0.5 * length;

  auto r_max = bin_from_r ?
    n_bins * bin_width : (n_bins-0.5) * bin_width;
  auto r_margined = r_max + margin;
  auto r2_max = r_max * r_max;
  auto r2_margined = r_margined * r_margined;

  for (int i = 0; i != 3; ++i)
  {
    if (limits(i) < r_margined)
    {
      ut::warning(
        "Box length is too short in " + Str("xyz").substr(i, 1));
    }
  }

  std::pair<int,int> shift_x = box.value("periodic_x", false) ?
    std::make_pair(-1, 1) : std::make_pair(0, 0);
  std::pair<int,int> shift_y = box.value("periodic_y", false) ?
    std::make_pair(-1, 1) : std::make_pair(0, 0);
  std::pair<int,int> shift_z = box.value("periodic_z", false) ?
    std::make_pair(-1, 1) : std::make_pair(0, 0);

  auto reciprocal_width = 1.0 / bin_width;

  // computation body

  number_traj[index] = n_beads;
  volume_traj[index] = length.prod();
  counts_traj[index] = ArrayXi::Zero(n_bins);

  auto &counts = counts_traj[index];

  for (int i = 0; i != n_beads; ++i)
  {
    auto sbs_i = special_bonds_exist ?
      beads[i]["special-bonds"].get<Set<int>>() : Set<int>();

    auto &tmp_i = rs_and_Is_per_mass[i];
    auto &r_i = tmp_i.first;
    auto &I_i = tmp_i.second;

    for (int j = i+1; j != n_beads; ++j)
    {
      if (!sbs_i.empty() && sbs_i.find(
        beads[j]["id"].get<int>()) != sbs_i.end()) continue;

      auto &tmp_j = rs_and_Is_per_mass[j];
      auto &I_j = tmp_j.second;

      auto dr_original = tmp_j.first - r_i;

      for (int ix = shift_x.first; ix <= shift_x.second; ++ix)
      {
        auto dx = dr_original(0) + ix*length(0);

        if (limits(0) < abs(dx)) continue;

        for (int iy = shift_y.first; iy <= shift_y.second; ++iy)
        {
          auto dy = dr_original(1) + iy*length(1);

          if (limits(1) < abs(dy)) continue;

          for (int iz = shift_z.first; iz <= shift_x.second; ++iz)
          {
            auto dz = dr_original(2) + iz*length(2);

            if (limits(2) < abs(dz)) continue;

            auto r2 = dx*dx + dy*dy + dz*dz;

            if (r2_margined <= r2) continue;

            auto e_ij = Eigen::Vector3d(dx, dy, dz);
            e_ij.normalize();

            auto quad_i = e_ij.transpose() * I_i * e_ij;
            auto quad_j = e_ij.transpose() * I_j * e_ij;

            auto Rg2_i = 0.5*I_i.trace();
            auto Rg2_j = 0.5*I_j.trace();

            // perpendicular (not used for now)
            //auto Rg2_perp_i = 1.5 * quad_i;
            //auto Rg2_perp_j = 1.5 * quad_j;

            // parallel
            auto Rg2_para_i = 3.0 * (Rg2_i - quad_i);
            auto Rg2_para_j = 3.0 * (Rg2_j - quad_j);

            auto r_modified = sqrt(r2) + (
              (sqrt(Rg2_i) - sqrt(Rg2_para_i)) +
              (sqrt(Rg2_j) - sqrt(Rg2_para_j)));

            /* NOTE:
              The below lines check if the mergin is efficiently large;
              no distance becomes out of range by the modification.
              This somewhat ensure that every modified distance smaller
              than `r_max` is counted (I made an assumption: if no
              distance goes from [0,r_max) to [r_margined,+inf), no
              distance goes from [r_margined,+inf) to [0,r_max) by the
              modification.
            */
            if (r2 < r2_max && r_margined <= r_modified)
            {
              ut::warning("Margin is too small");
            }

            auto index = bin_from_r ?
              floor(r_modified*reciprocal_width) :
              round(r_modified*reciprocal_width);

            counts(index) += 2;  // i -> j & j -> i
          }
        }
      }
    }
  }
}

/* ------------------------------------------------------------------ */
/*
void ProRDFWD::prepare()
{
  number_traj.resize(n_generators);
  volume_traj.resize(n_generators);
  counts_traj.resize(n_generators);
}

/* ------------------------------------------------------------------ */
/*
void ProRDFWD::finish()
{
  ArrayXd shell_volume(n_bins);

  double ball_coeff = 4.0 * M_PI / 3.0;

  for (int i = 0; i != n_bins; ++i)
  {
    auto r_inner = bin_from_r ?
      i * bin_width : std::max(0.0, (i-0.5) * bin_width);
    auto r_outer = bin_from_r ?
      (i+1) * bin_width : (i+0.5) * bin_width;

    shell_volume(i) = ball_coeff * (pow(r_outer, 3) - pow(r_inner, 3));
  }

  int number_sum = 0;
  double volume_sum = 0.0;
  ArrayXi counts_sum = ArrayXi::Zero(n_bins);

  rdf_traj.reserve(n_generators);

  for (int i = 0; i != n_generators; ++i)
  {
    auto number_tmp = number_traj[i];
    auto volume_tmp = volume_traj[i];
    auto counts_tmp = counts_traj[i];

    auto density_tmp = number_tmp / volume_tmp;
    auto number_distribution_tmp
      = counts_tmp.cast<double>() / double(number_tmp);

    rdf_traj.push_back(
      number_distribution_tmp / (density_tmp*shell_volume));

    number_sum += number_tmp;
    volume_sum += volume_tmp;
    counts_sum += counts_tmp;
  }

  auto density = number_sum / volume_sum;
  auto number_distribution
    = counts_sum.cast<double>() / double(number_sum);

  rdf = number_distribution / (density*shell_volume);

  number_traj.clear();
  number_traj.shrink_to_fit();
  volume_traj.clear();
  volume_traj.shrink_to_fit();
  counts_traj.clear();
  counts_traj.shrink_to_fit();
}

/* ------------------------------------------------------------------ */
/*
void ProRDFWD::set_bin(
  double bin_width_,
  int n_bins_)
{
  n_bins = n_bins_;
  bin_width = bin_width_;
}

/* ------------------------------------------------------------------ */

void ProRDFWD::set_margin(
  double margin_)
{
  margin = margin_;
}

/* ------------------------------------------------------------------ */
/*
void ProRDFWD::set_gyration_radius(
  double gyration_radius_)
{
  gyration_radius = gyration_radius_;
}

/* ------------------------------------------------------------------ */
/*
void ProRDFWD::bin_from_r_to_r_plus_dr(
  bool bin_from_r_)
{
  bin_from_r = bin_from_r_;
}

/* ------------------------------------------------------------------ */
/*
void ProRDFWD::beyond_half_box_length(
  bool beyond_half_)
{
  beyond_half = beyond_half_;
}

/* ------------------------------------------------------------------ */
/*
const ArrayXd ProRDFWD::get_r_axis()
{
  ArrayXd rs(n_bins);

  for (int i = 0; i != n_bins; ++i)
  {
    rs(i) = i * bin_width;
  }

  return rs;
}

/* ------------------------------------------------------------------ */
/*
const ArrayXd &ProRDFWD::get_rdf()
{
  return rdf;
}

/* ------------------------------------------------------------------ */
/*
const Vec<ArrayXd> &ProRDFWD::get_rdf_traj()
{
  return rdf_traj;
}
*/
