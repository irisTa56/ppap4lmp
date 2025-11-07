/*!
  @file src/processors/pro_radial_distribution_function.cpp
  @brief This file has an implementation of ProRadialDistributionFunction class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#define _USE_MATH_DEFINES

#include <cmath>

#include "pro_radial_distribution_function.h"
#include "../utils/message.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

ProRadialDistributionFunction::ProRadialDistributionFunction(
  const ElPtr &targets,
  const ElPtr &box)
{
  register_generator(ShPtr<GenDict>(
    new GenDict({{"Targets", targets}, {"Box", box}})));
}

/* ------------------------------------------------------------------ */

ProRadialDistributionFunction::ProRadialDistributionFunction(
  const Vec<std::pair<ElPtr,ElPtr>> &pairs)
{
  Vec<ShPtr<GenDict>> gens;

  for (const auto &pair : pairs)
  {
    gens.push_back(ShPtr<GenDict>(
      new GenDict({{"Targets", pair.first}, {"Box", pair.second}})));
  }

  register_generators(gens);
}

/* ------------------------------------------------------------------ */

void ProRadialDistributionFunction::run_impl(
  const int index)
{
  /* NOTE:
    Although 'atom' is used for variable names,
    RDF of something other than atoms can be computed too.
  */
  auto el_atoms = generators[index]->get_element("Targets");

  el_atoms->check_required_keys({"x", "y", "z", "id"});

  auto &atoms = el_atoms->get_data();

  auto special_bonds_exist = el_atoms->check_optional_keys("special-bonds");

  auto el_box = generators[index]->get_element("Box");

  el_box->check_required_keys({"lo_x", "lo_y", "lo_z", "hi_x", "hi_y", "hi_z"});

  auto &box = el_box->get_data();

  ArrayXXd rs;
  el_atoms->make_2darray_from_data(rs, {"x", "y", "z"});

  ArrayXd box_length(3);
  box_length << box["hi_x"].get<double>() - box["lo_x"].get<double>(),
            box["hi_y"].get<double>() - box["lo_y"].get<double>(),
            box["hi_z"].get<double>() - box["lo_z"].get<double>();

  ArrayXd neighbor_limits = beyond_half ? box_length : 0.5 * box_length;

  const auto r_max = bin_from_r ?
    n_bins * bin_width : (n_bins-0.5) * bin_width;
  const auto r2_max = r_max*r_max;

  for (int i = 0; i != 3; ++i)
  {
    if (neighbor_limits(i) < r_max)
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

  const auto n_atoms = atoms.size();

  number_traj[index] = n_atoms;
  volume_traj[index] = box_length.prod();
  counts_traj[index] = ArrayXi::Zero(n_bins);

  auto &counts = counts_traj[index];

  for (int i = 0; i != n_atoms; ++i)
  {
    auto sbonds_i = special_bonds_exist ?
      atoms[i]["special-bonds"].get<Set<int>>() : Set<int>();

    auto r_i = rs.row(i);

    for (int j = i+1; j != n_atoms; ++j)
    {
      if (!sbonds_i.empty() && sbonds_i.find(
        atoms[j]["id"].get<int>()) != sbonds_i.cend()) continue;

      auto dr_original = rs.row(j) - r_i;

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

            if (r2_max <= r2) continue;

            auto r = sqrt(r2);

            auto r_index = bin_from_r ?
              floor(r*reciprocal_bin_width) : round(r*reciprocal_bin_width);

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

void ProRadialDistributionFunction::prepare()
{
  number_traj.resize(n_generators);
  volume_traj.resize(n_generators);
  counts_traj.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProRadialDistributionFunction::finish()
{
  ArrayXd shell_volume(n_bins);

  const double ball_coeff = 4.0 * M_PI / 3.0;

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
    auto &number_tmp = number_traj[i];
    auto &volume_tmp = volume_traj[i];
    auto &counts_tmp = counts_traj[i];

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

void ProRadialDistributionFunction::set_bin(
  double bin_width_,
  int n_bins_)
{
  n_bins = n_bins_;
  bin_width = bin_width_;
}

/* ------------------------------------------------------------------ */

void ProRadialDistributionFunction::bin_from_r_to_r_plus_dr(
  bool bin_from_r_)
{
  bin_from_r = bin_from_r_;
}

/* ------------------------------------------------------------------ */

void ProRadialDistributionFunction::beyond_half_box_length(
  bool beyond_half_)
{
  beyond_half = beyond_half_;
}

/* ------------------------------------------------------------------ */

const ArrayXd ProRadialDistributionFunction::get_r_axis()
{
  ArrayXd rs(n_bins);

  for (int i = 0; i != n_bins; ++i)
  {
    rs(i) = i * bin_width;
  }

  return rs;
}

/* ------------------------------------------------------------------ */

const ArrayXd &ProRadialDistributionFunction::get_rdf()
{
  return rdf;
}

/* ------------------------------------------------------------------ */

const Vec<ArrayXd> &ProRadialDistributionFunction::get_rdf_traj()
{
  return rdf_traj;
}
