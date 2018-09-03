/* ---------------------------------------------------------------------
ProThicknessProfile: stands for Processor which computes Thickness
Profile from positions.

create: 2018/07/08 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "pro_thickness_profile.h"

/* ------------------------------------------------------------------ */

ProThicknessProfile::ProThicknessProfile(
  const ShPtr<Element> &atoms,
  const ShPtr<Element> &box)
{
  register_generator(ShPtr<GenDict>(
    new GenDict({{"Atoms", atoms}, {"Box", box}})));
}

/* ------------------------------------------------------------------ */

ProThicknessProfile::ProThicknessProfile(
  const Vec<std::pair<ShPtr<Element>,ShPtr<Element>>> &pairs)
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
  auto el_atoms = generators[index]->get_element("Atoms");

  el_atoms->required({"x", "y", "z", "radius"});

  auto mini_atoms = el_atoms->get_data({"x", "y", "z", "radius"});

  auto el_box = generators[index]->get_element("Box");

  el_box->required({"lo_x", "lo_y", "hi_x", "hi_y"});

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

  // computation body

  std::sort(
    mini_atoms.begin(), mini_atoms.end(),
    [](auto &a, auto &b)
    {
      return a["z"] > b["z"];
    });  // to improve speed

  ArrayXXd profile_tmp = ArrayXXd::Zero(nx, ny);

  auto reciprocal_nx = 1.0 / double(nx);
  auto reciprocal_ny = 1.0 / double(ny);
  auto reciprocal_delta_x = 1.0 / delta_x;
  auto reciprocal_delta_y = 1.0 / delta_y;

  auto n_atoms = mini_atoms.size();

  for (int i = 0; i != n_atoms; ++i)
  {
    auto atom = mini_atoms[i];

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

        auto ix_in_box = ix - floor(ix*reciprocal_nx)*nx;
        auto iy_in_box = iy - floor(iy*reciprocal_ny)*ny;

        auto dz2 = radius2 - dr2;

        auto d = atom_z - profile_tmp(ix_in_box, iy_in_box);

        if (d < 0.0 && dz2 < d*d) continue;

        profile_tmp(ix_in_box, iy_in_box) = atom_z + sqrt(dz2);
      }
    }
  }

  profiles[index] = profile_tmp;
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
