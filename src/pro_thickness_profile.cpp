/* ---------------------------------------------------------------------
ProThicknessProfile: stands for Processor which computes Thickness
Profile from positions of 'Atoms'.

create: 2018/07/08 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <algorithm>

#include "pro_thickness_profile.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

ProThicknessProfile::ProThicknessProfile(
  std::shared_ptr<Generator> gen) : Processor(gen)
{
  for (auto gen : generators)
  {
    if (gen->get_datatype() != "Dict(Atoms,Box)")
    {
      runtime_error(
        "ProThicknessProfile cannot use " + gen->get_dataname());
    }
  }
}

/* ------------------------------------------------------------------ */

ProThicknessProfile::ProThicknessProfile(
  std::vector<std::shared_ptr<Generator>> gens) : Processor(gens)
{
  for (auto gen : generators)
  {
    if (gen->get_datatype() != "Dict(Atoms,Box)")
    {
      runtime_error(
        "ProThicknessProfile cannot use " + gen->get_dataname());
    }
  }
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

const std::vector<json> &ProThicknessProfile::get_conditions()
{
  return conditions;
}

/* ------------------------------------------------------------------ */

const std::vector<Eigen::ArrayXXd> &ProThicknessProfile::get_profiles()
{
  return profiles;
}

/* ------------------------------------------------------------------ */

void ProThicknessProfile::run_impl(int index)
{
  auto gen_atoms = generators[index]->get_generator("Atoms");
  auto &atoms = gen_atoms->get_data();

  if (check_key(
    atoms, {"x", "y", "z", "radius"}) != json({true, true, true, true}))
  {
    runtime_error("ProThicknessProfile needs radii and wrapped positions");
  }

  auto mini_atoms = get_partial_json(atoms, {"x", "y", "z", "radius"});

  auto gen_box = generators[index]->get_generator("Box");
  auto &box = gen_box->get_data();

  auto origin_x = double(box["min_x"]);
  auto origin_y = double(box["min_y"]);
  auto delta_x = (double(box["max_x"]) - origin_x) / double(nx);
  auto delta_y = (double(box["max_y"]) - origin_y) / double(ny);

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
    });

  Eigen::ArrayXXd tmp = Eigen::ArrayXXd::Zero(nx, ny);

  double reciprocal_nx = 1.0 / double(nx);
  double reciprocal_ny = 1.0 / double(ny);
  double reciprocal_delta_x = 1.0 / delta_x;
  double reciprocal_delta_y = 1.0 / delta_y;

  int n_atoms = atoms.size();

  for (int i = 0; i != n_atoms; ++i)
  {
    auto atom = mini_atoms[i];

    double atom_x = atom["x"];
    double atom_y = atom["y"];
    double atom_z = atom["z"];

    atom_z -= offset;

    double radius = atom["radius"];
    double radius2 = radius*radius;

    int grid_index_min_x = ceil((atom_x-radius)*reciprocal_delta_x);
    int grid_index_min_y = ceil((atom_y-radius)*reciprocal_delta_y);
    int grid_index_max_x = ceil((atom_x+radius)*reciprocal_delta_x);
    int grid_index_max_y = ceil((atom_y+radius)*reciprocal_delta_y);

    for (int ix = grid_index_min_x; ix != grid_index_max_x; ++ix)
    {
      for (int iy = grid_index_min_y; iy != grid_index_max_y; ++iy)
      {
        auto grid_x = origin_x + ix*delta_x;
        auto grid_y = origin_y + iy*delta_y;

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

void ProThicknessProfile::prepare_impl()
{
  conditions.resize(n_generators);
  profiles.resize(n_generators);
}
