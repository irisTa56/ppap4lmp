/* ---------------------------------------------------------------------
ProRadialDistributionFunction: stands for Processor which computes
Radial Distribution Function (RDF) from wrapped positions.

create: 2018/08/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#define _USE_MATH_DEFINES

#include <cmath>

#include "pro_radial_distribution_function.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

ProRadialDistributionFunction::ProRadialDistributionFunction(
  ShPtr<GenElement> atoms,
  ShPtr<GenElement> box)
{
  register_generators(ShPtr<GenDict>(
    new GenDict({{"Atoms", atoms}, {"Box", box}})));
}

/* ------------------------------------------------------------------ */

ProRadialDistributionFunction::ProRadialDistributionFunction(
  List<std::pair<ShPtr<GenElement>,ShPtr<GenElement>>> pairs)
{
  List<ShPtr<GenDict>> gens;

  for (auto pair : pairs)
  {
    gens.push_back(ShPtr<GenDict>(
      new GenDict({{"Atoms", pair.first}, {"Box", pair.second}})));
  }

  register_generators(gens);
}

/* ------------------------------------------------------------------ */

void ProRadialDistributionFunction::run_impl(
  int index)
{
  auto gen_atoms = generators[index]->get_element("Atoms");
  auto &atoms = gen_atoms->get_data();

  check_keys(gen_atoms, {"x", "y", "z", "id"});

  bool special_bonds_exist = check_containment<Str>(
    gen_atoms->get_keys(), "special-bonds") ? true : false;

  auto gen_box = generators[index]->get_element("Box");
  auto &box = gen_box->get_data();

  check_keys(
    gen_box, {"lo_x", "lo_y", "lo_z", "hi_x", "hi_y", "hi_z"});

  ArrayXd length(3);
  length << box["hi_x"].get<double>() - box["lo_x"].get<double>(),
            box["hi_y"].get<double>() - box["lo_y"].get<double>(),
            box["hi_z"].get<double>() - box["lo_z"].get<double>();

  ArrayXd half_length = 0.5 * length;

  auto r_max = bin_from_r ?
    n_bins * bin_width : (n_bins-0.5) * bin_width;
  auto r2_max = r_max*r_max;

  for (const auto &dim : get_indexed_list<Str>({"x", "y", "z"}))
  {
    if (half_length(dim.first) < r_max)
    {
      message("WARNING! Box length is too short in " + dim.second);
    }
  }

  std::pair<int,int> shift_x = box.value("periodic_x", false) ?
    std::make_pair(-1, 1) : std::make_pair(0, 0);
  std::pair<int,int> shift_y = box.value("periodic_y", false) ?
    std::make_pair(-1, 1) : std::make_pair(0, 0);
  std::pair<int,int> shift_z = box.value("periodic_z", false) ?
    std::make_pair(-1, 1) : std::make_pair(0, 0);

  ArrayXi counts = ArrayXi::Zero(n_bins);

  auto reciprocal_width = 1.0 / bin_width;

  for (const auto &atom_i : atoms)
  {
    for (const auto &atom_j : atoms)
    {
      if (!(atom_i["id"] < atom_j["id"])) continue;

      if (special_bonds_exist)
      {
        Set<int> sbonds = atom_i["special-bonds"];

        if (sbonds.find(atom_j["id"]) != sbonds.end()) continue;
      }

      auto dx_original
        = atom_j["x"].get<double>() - atom_i["x"].get<double>();
      auto dy_original
        = atom_j["y"].get<double>() - atom_i["y"].get<double>();
      auto dz_original
        = atom_j["z"].get<double>() - atom_i["z"].get<double>();

      for (int ix = shift_x.first; ix <= shift_x.second; ++ix)
      {
        auto dx = dx_original + ix*length(0);

        if (half_length(0) < abs(dx)) continue;

        for (int iy = shift_y.first; iy <= shift_y.second; ++iy)
        {
          auto dy = dy_original + iy*length(1);

          if (half_length(1) < abs(dy)) continue;

          for (int iz = shift_z.first; iz <= shift_x.second; ++iz)
          {
            auto dz = dz_original + iz*length(2);

            if (half_length(2) < abs(dz)) continue;

            auto r2 = dx*dx + dy*dy + dz*dz;

            if (r2_max <= r2) continue;

            auto r = sqrt(r2);

            auto index = bin_from_r ?
              floor(r*reciprocal_width) : round(r*reciprocal_width);

            counts(index) += 2;  // i -> j & j -> i
          }
        }
      }
    }
  }

  double n_atoms = atoms.size();

  density_traj[index] = n_atoms / length.prod();
  number_distribution_traj[index] = counts.cast<double>() / n_atoms;
}

/* ------------------------------------------------------------------ */

void ProRadialDistributionFunction::prepare()
{
  density_traj.resize(n_generators);
  number_distribution_traj.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProRadialDistributionFunction::finish()
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

  double density_sum = 0.0;
  ArrayXd number_distribution_sum = ArrayXd::Zero(n_bins);

  for (int i = 0; i != n_generators; ++i)
  {
    density_sum += density_traj[i];
    number_distribution_sum += number_distribution_traj[i];

    rdf_traj.push_back(
      number_distribution_traj[i] / (density_traj[i]*shell_volume));
  }

  auto reciprocal_num = 1.0 / double(n_generators);

  auto density = density_sum * reciprocal_num;
  auto number_distribution = number_distribution_sum * reciprocal_num;

  rdf = number_distribution / (density*shell_volume);
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

const List<ArrayXd> &ProRadialDistributionFunction::get_rdf_traj()
{
  return rdf_traj;
}
