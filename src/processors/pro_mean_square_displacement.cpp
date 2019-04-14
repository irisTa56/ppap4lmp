/*!
  @file src/processors/pro_mean_square_displacement.cpp
  @brief This file has an implementation of ProMeanSquareDisplacement class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/08/26
*/

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

void ProMeanSquareDisplacement::extract_positions(
  ArrayXXd &positions,
  const ElPtr &elem)
{
  // NOTE: `id` property is check_required_keys to ensure data is sorted.
  elem->check_required_keys({"xu", "yu", "zu", "id"});

  elem->make_2darray_from_data(positions, {"xu", "yu", "zu"});

  if (drift_correction)
  {
    elem->check_required_keys("mass");

    ArrayXd ms;
    elem->make_1darray_from_data(ms, "mass");

    auto com = (positions.colwise()*ms).colwise().sum() / ms.sum();

    positions.rowwise() -= com;
  }
}

/* ------------------------------------------------------------------ */

void ProMeanSquareDisplacement::run_impl(
  const int index)
{
  ArrayXXd rs;
  extract_positions(rs, generators[index]->get_element());

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
  use_generator_at(0);

  extract_positions(initial_rs, generators.front()->get_element());

  displacement2_traj.resize(n_generators);
}

/* ------------------------------------------------------------------ */

void ProMeanSquareDisplacement::finish()
{
  const auto n_points = displacement2_traj.front().size();

  for (const auto &sd : displacement2_traj)
  {
    if (n_points != sd.size())
    {
      ut::runtime_error("Data sizes must be the same");
    }
  }

  displacement2_array = ArrayXXd(n_generators, n_points);

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
