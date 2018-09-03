/* ---------------------------------------------------------------------
ProMeanSquareDisplacement: stands for Processor which computes Mean
Square Displacement.

create: 2018/08/26 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "pro_mean_square_displacement.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

ProMeanSquareDisplacement::ProMeanSquareDisplacement(
  const Vec<ElPtr> &elems)
{
  register_generators(elems);
}

/* ------------------------------------------------------------------ */

void ProMeanSquareDisplacement::run_impl(
  const int index)
{
  auto el_points = generators[index]->get_element();

  // if atoms have 'id', they are already sorted by 'id'
  el_points->required({"xu", "yu", "zu", "id"});

  ArrayXXd rs;
  el_points->array2d(rs, {"xu", "yu", "zu"});

  if (drift_correction)
  {
    el_points->required("mass");

    ArrayXd ms;
    el_points->array1d(ms, "mass");

    auto reciprocal = 1.0 / ms.sum();

    auto com = (rs.colwise()*ms).colwise().sum() * reciprocal;

    rs.rowwise() -= com;
  }

  auto displacement2_xyz = (rs - initial_rs).square();

  ArrayXd displacement2 = ArrayXd::Zero(displacement2_xyz.rows());

  for (int i = 0; i != 3; ++i)
  {
    if (dimension[i])
    {
      displacement2 += displacement2_xyz.col(i);
    }
  }

  displacement2_traj[index] = displacement2.transpose();
}

/* ------------------------------------------------------------------ */

void ProMeanSquareDisplacement::prepare()
{
  auto el_initial_points = generators.front()->get_element();

  el_initial_points->hello();

  el_initial_points->required({"xu", "yu", "zu", "id"});

  el_initial_points->array2d(initial_rs, {"xu", "yu", "zu"});

  if (drift_correction)
  {
    el_initial_points->required("mass");

    ArrayXd ms;
    el_initial_points->array1d(ms, "mass");

    auto reciprocal = 1.0 / ms.sum();

    auto com = (initial_rs.colwise()*ms).colwise().sum() * reciprocal;

    initial_rs.rowwise() -= com;
  }

  displacement2_traj.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProMeanSquareDisplacement::finish()
{
  auto size = displacement2_traj.front().size();

  for (const auto &sd : displacement2_traj)
  {
    if (size != sd.size())
    {
      ut::runtime_error("Data sizes must be the same");
    }
  }

  displacement2_array = ArrayXXd(n_generators, size);

  for (int i = 0; i != n_generators; ++i)
  {
    displacement2_array.row(i) = displacement2_traj[i];
  }

  mean_square_displacement = displacement2_array.rowwise().mean();

  displacement2_traj.clear();
  displacement2_traj.shrink_to_fit();
}

/* ------------------------------------------------------------------ */

void ProMeanSquareDisplacement::set_dimension(
  bool include_x,
  bool include_y,
  bool include_z)
{
  dimension = {include_x, include_y, include_z};
}

/* ------------------------------------------------------------------ */

void ProMeanSquareDisplacement::without_drift_correction(
  bool without_drift_correction_)
{
  drift_correction = !without_drift_correction_;
}

/* ------------------------------------------------------------------ */

const ArrayXXd &ProMeanSquareDisplacement::get_displacement2_array()
{
  return displacement2_array;
}

/* ------------------------------------------------------------------ */

const ArrayXd &ProMeanSquareDisplacement::get_mean_square_displacement()
{
  return mean_square_displacement;
}
