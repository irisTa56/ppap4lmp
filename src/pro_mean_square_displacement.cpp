/* ---------------------------------------------------------------------
ProMeanSquareDisplacement: stands for Processor which computes Mean
Square Displacement.

create: 2018/08/26 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "pro_mean_square_displacement.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

ProMeanSquareDisplacement::ProMeanSquareDisplacement(
  List<ShPtr<GenElement>> elems)
{
  register_generators(elems);
}

/* ------------------------------------------------------------------ */

void ProMeanSquareDisplacement::run_impl(
  int index)
{
  auto gen_points = generators[index]->get_element();

  check_keys(gen_points, {"xu", "yu", "zu", "id"});

  auto rs = gen_points->get_2d_double({"xu", "yu", "zu"});

  if (drift_correction)
  {
    check_key(gen_points, "mass");

    auto ms = gen_points->get_1d_double("mass");

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
  auto gen_initial_points = generators.front()->get_element();

  gen_initial_points->hello();

  check_keys(gen_initial_points, {"xu", "yu", "zu", "id"});

  initial_rs = gen_initial_points->get_2d_double({"xu", "yu", "zu"});

  if (drift_correction)
  {
    check_key(gen_initial_points, "mass");

    auto ms = gen_initial_points->get_1d_double("mass");

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
      runtime_error(
        "ProMeanSquareDisplacement: Data sizes must be the same");
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
