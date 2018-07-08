/* ---------------------------------------------------------------------
ProThicknessProfile: stands for Processor which computes Thickness
Profile from positions of 'Atoms'.

create: 2018/07/08 by Takayuki Kobayashi
--------------------------------------------------------------------- */

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

  if (check_key(atoms, {"x", "y", "z"}) != json({true, true, true}))
  {
    runtime_error("ProThicknessProfile needs wrapped positions");
  }

  if (!check_key(atoms, "radius"))
  {
    runtime_error("ProThicknessProfile needs radii");
  }

  auto rs = gen_atoms->get_2d_double({"x", "y", "z"});
  rs.col(2) -= offset;

  auto radii = gen_atoms->get_1d_double("radius");

  auto gen_box = generators[index]->get_generator("Box");
  auto &box = gen_box->get_data();

  auto origin_x = double(box["min_x"]);
  auto origin_y = double(box["min_y"]);
  auto length_x = double(box["max_x"]) - origin_x;
  auto length_y = double(box["max_y"]) - origin_y;
  auto delta_x = length_x / double(nx);
  auto delta_y = length_y / double(ny);
  auto half_x = 0.5 * length_x;
  auto half_y = 0.5 * length_y;

  conditions[index] = {
    {"origin_x", origin_x}, {"origin_y", origin_y},
    {"delta_x", delta_x}, {"delta_y", delta_y},
    {"nx", nx}, {"ny", ny}};

  // computation body

  Eigen::ArrayXXd tmp = Eigen::ArrayXXd::Zero(nx, ny);

  int n_atoms = atoms.size();

  for (int ix = 0; ix != nx; ++ix)
  {
    auto x = origin_x + (ix+0.5)*delta_x;

    for (int iy = 0; iy != ny; ++iy)
    {
      auto y = origin_y + (iy+0.5)*delta_y;

      for (int i = 0; i != n_atoms; ++i)
      {
        auto radius = radii(i);
        auto radius2 = radius * radius;

        // filter by distance in x direction

        auto dx = rs(i, 0) - x;

        if (dx < -half_x)
        {
          dx += length_x;
        }
        else if (dx > half_x)
        {
          dx -= length_x;
        }

        if (radius < dx)
        {
          continue;
        }

        // filter by distance in y direction

        auto dy = rs(i, 1) - y;

        if (dy < -half_y)
        {
          dy += length_y;
        }
        else if (dy > half_y)
        {
          dy -= length_y;
        }

        if (radius < dy)
        {
          continue;
        }

        // filter by distance

        auto dr2 = dx*dx + dy*dy;

        if (radius2 < dr2)
        {
          continue;
        }

        // update

        auto dz2 = radius2 - dr2;

        auto d = rs(i, 2) - tmp(ix, iy);

        if (d < 0.0 && dz2 < d*d)
        {
          continue;
        }

        tmp(ix, iy) += d + sqrt(dz2);
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
