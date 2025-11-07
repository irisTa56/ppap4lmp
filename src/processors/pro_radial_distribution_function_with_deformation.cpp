/*!
  @file src/processors/pro_radial_distribution_function_with_deformation.cpp
  @brief This file has an implementation of ProRadialDistributionFunctionWithDeformation class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#include "pro_radial_distribution_function_with_deformation.h"
#include "../utils/message.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void ProRDFWD::run_impl(
  const int index)
{
  /* NOTE:
    Although 'bead' is used for variable names,
    RDF of something other than beads can be computed too.
  */
  auto el_beads = generators[index]->get_element("Targets");

  el_beads->check_required_keys({
    "I_xx", "I_yy", "I_zz", "I_xy", "I_xz", "I_yz", "mass",
    "x", "y", "z", "id"});

  auto &beads = el_beads->get_data();

  auto special_bonds_exist = el_beads->check_optional_keys("special-bonds");

  auto el_box = generators[index]->get_element("Box");

  el_box->check_required_keys({"lo_x", "lo_y", "lo_z", "hi_x", "hi_y", "hi_z"});

  auto &box = el_box->get_data();

  // prepare

  const auto n_beads = beads.size();

  Vec<std::pair<Vector3d,Matrix3d>> rs_and_Is_per_mass;
  rs_and_Is_per_mass.reserve(n_beads);

  for (const auto &bead : beads)
  {
    rs_and_Is_per_mass.push_back(std::make_pair(
      (Vector3d() << bead["x"], bead["y"], bead["z"]).finished(),
      (Matrix3d() << bead["I_xx"], bead["I_xy"], bead["I_xz"],
                     bead["I_xy"], bead["I_yy"], bead["I_yz"],
                     bead["I_xz"], bead["I_yz"], bead["I_zz"]).finished()
        / bead["mass"].get<double>()));
  }

  ArrayXd box_length(3);
  box_length << box["hi_x"].get<double>() - box["lo_x"].get<double>(),
                box["hi_y"].get<double>() - box["lo_y"].get<double>(),
                box["hi_z"].get<double>() - box["lo_z"].get<double>();

  ArrayXd neighbor_limits = beyond_half ? box_length : 0.5 * box_length;

  const auto r_max = bin_from_r ? n_bins * bin_width : (n_bins-0.5) * bin_width;
  const auto r_margined = r_max + margin;
  const auto r2_max = r_max * r_max;
  const auto r2_margined = r_margined * r_margined;

  for (int i = 0; i != 3; ++i)
  {
    if (neighbor_limits(i) < r_margined)
    {
      ut::warning(
        "Box length is too short in " + Str("xyz").substr(i, 1));
    }
  }

  const std::pair<int,int> image_range_x = box.value("pbc_x", false) ?
    std::make_pair(-1, 1) : std::make_pair(0, 0);
  const std::pair<int,int> image_range_y = box.value("pbc_y", false) ?
    std::make_pair(-1, 1) : std::make_pair(0, 0);
  const std::pair<int,int> image_range_z = box.value("pbc_z", false) ?
    std::make_pair(-1, 1) : std::make_pair(0, 0);

  const auto reciprocal_bin_width = 1.0 / bin_width;

  const double one_third = 1.0 / 3.0;
  const double two_thirds = 2.0 / 3.0;

  // loop over all pairs of beads

  number_traj[index] = n_beads;
  volume_traj[index] = box_length.prod();

  counts_traj[index] = ArrayXi::Zero(n_bins);
  auto &counts = counts_traj[index];

  raw_counts_traj[index] = ArrayXi::Zero(n_bins);
  auto &raw_counts = raw_counts_traj[index];

  Rg2_sum_traj[index] = ArrayXd::Zero(n_bins);
  auto &Rg2_sum = Rg2_sum_traj[index];

  Rg2_para_sum_traj[index] = ArrayXd::Zero(n_bins);
  auto &Rg2_para_sum = Rg2_para_sum_traj[index];

  Rg2_perp_sum_traj[index] = ArrayXd::Zero(n_bins);
  auto &Rg2_perp_sum = Rg2_perp_sum_traj[index];

  for (int i = 0; i != n_beads; ++i)
  {
    auto sbonds_i = special_bonds_exist ?
      beads[i]["special-bonds"].get<Set<int>>() : Set<int>();

    auto &tmp_i = rs_and_Is_per_mass[i];
    auto &r_i = tmp_i.first;
    auto &I_i = tmp_i.second;

    for (int j = i+1; j != n_beads; ++j)
    {
      if (!sbonds_i.empty() && sbonds_i.find(
        beads[j]["id"].get<int>()) != sbonds_i.cend()) continue;

      auto &tmp_j = rs_and_Is_per_mass[j];
      auto &I_j = tmp_j.second;

      auto dr_original = tmp_j.first - r_i;

      for (int ix = image_range_x.first; ix <= image_range_x.second; ++ix)
      {
        auto dx = dr_original(0) + ix*box_length(0);

        if (neighbor_limits(0) < abs(dx)) continue;

        for (int iy = image_range_y.first; iy <= image_range_y.second; ++iy)
        {
          auto dy = dr_original(1) + iy*box_length(1);

          if (neighbor_limits(1) < abs(dy)) continue;

          for (int iz = image_range_z.first; iz <= image_range_z.second; ++iz)
          {
            auto dz = dr_original(2) + iz*box_length(2);

            if (neighbor_limits(2) < abs(dz)) continue;

            auto r2 = dx*dx + dy*dy + dz*dz;

            if (r2_margined <= r2) continue;

            Vector3d e_ij;
            e_ij << dx, dy, dz;
            e_ij.normalize();

            auto Rg2_i = 0.5 * I_i.trace();
            auto Rg2_j = 0.5 * I_j.trace();

            /* NOTE:
              Using `auto` leads to an Eigen related error (I cannot
              figure out the details).
            */
            double Rg2_perp_i = 1.5 * e_ij.transpose() * I_i * e_ij;
            double Rg2_perp_j = 1.5 * e_ij.transpose() * I_j * e_ij;

            auto Rg2_para_i = 3.0 * (Rg2_i - two_thirds*Rg2_perp_i);
            auto Rg2_para_j = 3.0 * (Rg2_j - two_thirds*Rg2_perp_j);

            auto r = sqrt(r2);

            if (r < r_max)
            {
              auto r_index = bin_from_r ?
                floor(r*reciprocal_bin_width) : round(r*reciprocal_bin_width);

              raw_counts(static_cast<int>(r_index)) += 2;
              Rg2_sum(static_cast<int>(r_index)) += Rg2_i + Rg2_j;
              Rg2_para_sum(static_cast<int>(r_index)) += Rg2_para_i + Rg2_para_j;
              Rg2_perp_sum(static_cast<int>(r_index)) += Rg2_perp_i + Rg2_perp_j;
            }

            auto r_modified = r + (
              (sqrt(one_third*Rg2_i) - sqrt(one_third*Rg2_para_i)) +
              (sqrt(one_third*Rg2_j) - sqrt(one_third*Rg2_para_j)));

            /* NOTE:
              The below lines check if the margin is efficiently large;
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

            if (r_max <= r_modified)
            {
              continue;
            }
            else if (r_max < 0.0)
            {
              ut::runtime_error("Deformation might be too large");
            }

            auto r_index = bin_from_r ?
              floor(r_modified*reciprocal_bin_width) :
              round(r_modified*reciprocal_bin_width);

            /* NOTE:
              Adding 2 (not 1) is for taking both directions
              (i -> j & j -> i) into consideration at once.
            */
            counts(static_cast<int>(r_index)) += 2;
          }
        }
      }
    }
  }
}

/* ------------------------------------------------------------------ */

void ProRDFWD::prepare()
{
  ProRDF::prepare();

  raw_counts_traj.resize(n_generators);
  Rg2_sum_traj.resize(n_generators);
  Rg2_para_sum_traj.resize(n_generators);
  Rg2_perp_sum_traj.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProRDFWD::finish()
{
  ProRDF::finish();

  Rg2_array_traj.resize(n_generators);
  Rg2_para_array_traj.resize(n_generators);
  Rg2_perp_array_traj.resize(n_generators);

  // NOTE: Do not use `auto` for initialization using Eigen's Zero().
  ArrayXi counts_sum = ArrayXi::Zero(n_bins);
  ArrayXd Rg2_sum = ArrayXd::Zero(n_bins);
  ArrayXd Rg2_para_sum = ArrayXd::Zero(n_bins);
  ArrayXd Rg2_perp_sum = ArrayXd::Zero(n_bins);

  for (int i = 0; i != n_generators; ++i)
  {
    auto &counts_tmp = raw_counts_traj[i];
    auto &Rg2_tmp = Rg2_sum_traj[i];
    auto &Rg2_para_tmp = Rg2_para_sum_traj[i];
    auto &Rg2_perp_tmp = Rg2_perp_sum_traj[i];

    auto reciprocal_counts = (1.0 / counts_tmp.cast<double>())
    .unaryExpr([](double x)
    {
      return std::isfinite(x) ? x : 0.0;
    });

    Rg2_array_traj[i] = Rg2_tmp * reciprocal_counts;
    Rg2_para_array_traj[i] = Rg2_para_tmp * reciprocal_counts;
    Rg2_perp_array_traj[i] = Rg2_perp_tmp * reciprocal_counts;

    counts_sum += counts_tmp;
    Rg2_sum += Rg2_tmp;
    Rg2_para_sum += Rg2_para_tmp;
    Rg2_perp_sum += Rg2_perp_tmp;
  }

  auto reciprocal_counts = (1.0 / counts_sum.cast<double>())
    .unaryExpr([](double x)
    {
      return std::isfinite(x) ? x : 0.0;
    });

  Rg2_array = Rg2_sum * reciprocal_counts;
  Rg2_para_array = Rg2_para_sum * reciprocal_counts;
  Rg2_perp_array = Rg2_perp_sum * reciprocal_counts;

  raw_counts_traj.clear();
  raw_counts_traj.shrink_to_fit();
  Rg2_sum_traj.clear();
  Rg2_sum_traj.shrink_to_fit();
  Rg2_para_sum_traj.clear();
  Rg2_para_sum_traj.shrink_to_fit();
  Rg2_perp_sum_traj.clear();
  Rg2_perp_sum_traj.shrink_to_fit();
}

/* ------------------------------------------------------------------ */

void ProRDFWD::set_margin(
  double margin_)
{
  margin = margin_;
}

/* ------------------------------------------------------------------ */

Map<Str,ArrayXd> ProRDFWD::get_gyration_radius()
{
  return {
    {"isotropic", Rg2_array.sqrt()},
    {"parallel", Rg2_para_array.sqrt()},
    {"perpendicular", Rg2_perp_array.sqrt()}};
}

/* ------------------------------------------------------------------ */

Map<Str,Vec<ArrayXd>> ProRDFWD::get_gyration_radius_traj()
{
  Map<Str,Vec<ArrayXd>> type2traj;

  auto &iso = type2traj["isotropic"];

  for (const auto &array : Rg2_array_traj)
  {
    iso.push_back(array.sqrt());
  }

  auto &para = type2traj["parallel"];

  for (const auto &array : Rg2_array_traj)
  {
    para.push_back(array.sqrt());
  }

  auto &perp = type2traj["perpendicular"];

  for (const auto &array : Rg2_array_traj)
  {
    perp.push_back(array.sqrt());
  }

  return type2traj;
}

/* ------------------------------------------------------------------ */

Map<Str,ArrayXd> ProRDFWD::get_squared_gyration_radius()
{
  return {
    {"isotropic", Rg2_array},
    {"parallel", Rg2_para_array},
    {"perpendicular", Rg2_perp_array}};
}

/* ------------------------------------------------------------------ */

Map<Str,Vec<ArrayXd>> ProRDFWD::get_squared_gyration_radius_traj()
{
  return {
    {"isotropic", Rg2_array_traj},
    {"parallel", Rg2_para_array_traj},
    {"perpendicular", Rg2_perp_array_traj}};
}
