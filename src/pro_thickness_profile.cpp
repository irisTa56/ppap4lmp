/* ---------------------------------------------------------------------
ProThicknessProfile: stands for Processor which computes Thickness
Profile from positions of 'Atoms'.

create: 2018/07/08 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "pro_thickness_profile.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

ProThicknessProfile::ProThicknessProfile(
  ShPtr<GenElement> atoms, ShPtr<GenElement> box)
{
  register_generators(ShPtr<GenDict>(
    new GenDict({{"Atoms", atoms}, {"Box", box}})));
}

/* ------------------------------------------------------------------ */

ProThicknessProfile::ProThicknessProfile(
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

void ProThicknessProfile::run_impl(int index)
{
  auto gen_atoms = generators[index]->get_element("Atoms");
  auto &atoms = gen_atoms->get_data();

  if (!check_containment<Str>(
    gen_atoms->get_keys(), {"x", "y", "z", "radius"}))
  {
    runtime_error(
      "ProThicknessProfile needs 'x', 'y', 'z' and 'radius'");
    return;
  }

  auto mini_atoms = get_partial_json(atoms, {"x", "y", "z", "radius"});

  auto gen_box = generators[index]->get_element("Box");
  auto &box = gen_box->get_data();

  if (!check_containment<Str>(
    gen_box->get_keys(), {"lo_x", "lo_y", "hi_x", "hi_y"}))
  {
    runtime_error("ProThicknessProfile needs 'lo_*' and 'hi_*' (x/y)");
    return;
  }

  auto origin_x = box["lo_x"].get<double>();
  auto origin_y = box["lo_y"].get<double>();
  auto delta_x = (box["hi_x"].get<double>() - origin_x) / double(nx);
  auto delta_y = (box["hi_y"].get<double>() - origin_y) / double(ny);

  if (shift_half_delta)
  {
    origin_x += 0.5 * delta_x;
    origin_y += 0.5 * delta_y;
  }

  conditions[index] = {
    {"origin_x", origin_x}, {"origin_y", origin_y},
    {"delta_x", delta_x}, {"delta_y", delta_y},
    {"nx", nx}, {"ny", ny}};

  // computation body

  descending_sort_by("z", mini_atoms);  // to improve speed

  ArrayXXd tmp = ArrayXXd::Zero(nx, ny);

  auto reciprocal_nx = 1.0 / double(nx);
  auto reciprocal_ny = 1.0 / double(ny);
  auto reciprocal_delta_x = 1.0 / delta_x;
  auto reciprocal_delta_y = 1.0 / delta_y;

  int n_atoms = atoms.size();

  for (int i = 0; i != n_atoms; ++i)
  {
    auto atom = mini_atoms[i];

    auto atom_x = atom["x"].get<double>() - origin_x;
    auto atom_y = atom["y"].get<double>() - origin_y;
    auto atom_z = atom["z"].get<double>() - offset;

    auto radius = atom["radius"].get<double>();
    auto radius2 = radius*radius;

    int grid_index_min_x = ceil((atom_x-radius)*reciprocal_delta_x);
    int grid_index_min_y = ceil((atom_y-radius)*reciprocal_delta_y);
    int grid_index_max_x = ceil((atom_x+radius)*reciprocal_delta_x);
    int grid_index_max_y = ceil((atom_y+radius)*reciprocal_delta_y);

    for (int ix = grid_index_min_x; ix != grid_index_max_x; ++ix)
    {
      for (int iy = grid_index_min_y; iy != grid_index_max_y; ++iy)
      {
        auto grid_x = ix*delta_x;
        auto grid_y = iy*delta_y;

        auto dx = atom_x - grid_x;
        auto dy = atom_y - grid_y;
        auto dr2 = dx*dx + dy*dy;

        if (radius2 < dr2)
        {
          continue;
        }

        int ix_in_box = ix - floor(ix*reciprocal_nx)*nx;
        int iy_in_box = iy - floor(iy*reciprocal_ny)*ny;

        auto dz2 = radius2 - dr2;

        auto d = atom_z - tmp(ix_in_box, iy_in_box);

        if (d < 0.0 && dz2 < d*d)
        {
          continue;
        }

        tmp(ix_in_box, iy_in_box) = atom_z + sqrt(dz2);
      }
    }
  }

  profiles[index] = tmp;
}

/* ------------------------------------------------------------------ */

void ProThicknessProfile::prepare()
{
  conditions.resize(n_generators);
  profiles.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProThicknessProfile::set_grid(int nx_, int ny_)
{
  nx = nx_;
  ny = ny_;
}

/* ------------------------------------------------------------------ */

void ProThicknessProfile::set_offset(double offset_)
{
  offset = offset_;
}

/* ------------------------------------------------------------------ */

void ProThicknessProfile::set_shift_half_delta(bool shift_half_delta_)
{
  shift_half_delta = shift_half_delta_;
}

/* ------------------------------------------------------------------ */

const List<Json> &ProThicknessProfile::get_conditions()
{
  return conditions;
}

/* ------------------------------------------------------------------ */

const List<ArrayXXd> &ProThicknessProfile::get_profiles()
{
  return profiles;
}
