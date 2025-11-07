/*!
  @file src/processors/pro_thickness_profile.cpp
  @brief This file has an implementation of ProThicknessProfile class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/07/08
*/

#include "pro_thickness_profile.h"

/* ------------------------------------------------------------------ */

ProThicknessProfile::ProThicknessProfile(
  const ElPtr &atoms,
  const ElPtr &box)
{
  register_generator(ShPtr<GenDict>(
    new GenDict({{"Atoms", atoms}, {"Box", box}})));
}

/* ------------------------------------------------------------------ */

ProThicknessProfile::ProThicknessProfile(
  const Vec<std::pair<ElPtr,ElPtr>> &pairs)
{
  Vec<ShPtr<GenDict>> gens;

  for (const auto &pair : pairs)
  {
    gens.push_back(ShPtr<GenDict>(
      new GenDict({{"Atoms", pair.first}, {"Box", pair.second}})));
  }

  register_generators(gens);
}

/* ------------------------------------------------------------------ */

void ProThicknessProfile::run_impl(
  const int index)
{
  /* NOTE:
    Although 'atom' is used for variable names,
    profile thickness of something other than atoms can be computed too.
  */
  auto el_atoms = generators[index]->get_element("Atoms");

  el_atoms->check_required_keys({"x", "y", "z", "radius"});

  auto atoms = el_atoms->make_reduced_data({"x", "y", "z", "radius"});

  auto el_box = generators[index]->get_element("Box");

  el_box->check_required_keys({"lo_x", "lo_y", "hi_x", "hi_y"});

  auto &box = el_box->get_data();

  auto origin_x = box["lo_x"].get<double>();
  auto origin_y = box["lo_y"].get<double>();
  auto delta_x = (box["hi_x"].get<double>() - origin_x) / double(nx);
  auto delta_y = (box["hi_y"].get<double>() - origin_y) / double(ny);

  if (shift_half)
  {
    origin_x += 0.5 * delta_x;
    origin_y += 0.5 * delta_y;
  }

  conditions[index] = {
    {"origin_x", origin_x}, {"origin_y", origin_y},
    {"delta_x", delta_x}, {"delta_y", delta_y},
    {"nx", nx}, {"ny", ny}};

  /* NOTE:
    Sorting atoms in descending order of height (coordinate in z
    direction) can speed up this analysis significantly.
  */
  std::sort(
    atoms.begin(), atoms.end(),
    [](auto &a, auto &b) { return a["z"] > b["z"]; });

  // loop over all atoms

  profiles[index] = ArrayXXd::Zero(nx, ny);
  auto &profile_tmp = profiles[index];

  const auto reciprocal_nx = 1.0 / double(nx);
  const auto reciprocal_ny = 1.0 / double(ny);
  const auto reciprocal_delta_x = 1.0 / delta_x;
  const auto reciprocal_delta_y = 1.0 / delta_y;

  auto n_atoms = atoms.size();

  for (int i = 0; i != n_atoms; ++i)
  {
    auto atom = atoms[i];

    auto atom_x = atom["x"].get<double>() - origin_x;
    auto atom_y = atom["y"].get<double>() - origin_y;
    auto atom_z = atom["z"].get<double>() - offset;

    auto radius = atom["radius"].get<double>();
    auto radius2 = radius*radius;

    auto grid_index_min_x = ceil((atom_x-radius)*reciprocal_delta_x);
    auto grid_index_min_y = ceil((atom_y-radius)*reciprocal_delta_y);
    auto grid_index_max_x = ceil((atom_x+radius)*reciprocal_delta_x);
    auto grid_index_max_y = ceil((atom_y+radius)*reciprocal_delta_y);

    for (int ix = grid_index_min_x; ix != grid_index_max_x; ++ix)
    {
      for (int iy = grid_index_min_y; iy != grid_index_max_y; ++iy)
      {
        auto grid_x = ix*delta_x;
        auto grid_y = iy*delta_y;

        auto dx = atom_x - grid_x;
        auto dy = atom_y - grid_y;
        auto dr2 = dx*dx + dy*dy;

        if (radius2 < dr2) continue;

        Eigen::Index ix_in_box = static_cast<Eigen::Index>(ix - floor(ix*reciprocal_nx)*nx);
        Eigen::Index iy_in_box = static_cast<Eigen::Index>(iy - floor(iy*reciprocal_ny)*ny);

        auto dz2 = radius2 - dr2;

        double d = atom_z - profile_tmp(ix_in_box, iy_in_box);

        if (d < 0.0 && dz2 < d*d) continue;

        profile_tmp(ix_in_box, iy_in_box) = atom_z + sqrt(dz2);
      }
    }
  }
}

/* ------------------------------------------------------------------ */

void ProThicknessProfile::prepare()
{
  conditions.resize(n_generators);
  profiles.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProThicknessProfile::set_grid(
  int nx_,
  int ny_)
{
  nx = nx_;
  ny = ny_;
}

/* ------------------------------------------------------------------ */

void ProThicknessProfile::set_offset(
  double offset_)
{
  offset = offset_;
}

/* ------------------------------------------------------------------ */

void ProThicknessProfile::shift_half_delta(
  bool shift_half_)
{
  shift_half = shift_half_;
}

/* ------------------------------------------------------------------ */

const Vec<Json> &ProThicknessProfile::get_conditions()
{
  return conditions;
}

/* ------------------------------------------------------------------ */

const Vec<ArrayXXd> &ProThicknessProfile::get_profiles()
{
  return profiles;
}
