/*!
  @file src/adders/add_molecular_orientation.cpp
  @brief This file has an implementation of AddMolecularOrientation
  class, which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/16
  @details For more details, please see the header file,
  src/adders/add_molecular_orientation.h.
*/

#include <Eigen/Eigenvalues>

#include "add_molecular_orientation.h"

/* ------------------------------------------------------------------ */

void AddMolecularOrientation::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  datakeys.required({"I_xx", "I_yy", "I_zz", "I_xy", "I_xz", "I_yz"});

  for (auto &d : data)
  {
    // compute principal values and vectors

    Matrix3d inertia_moment;
    inertia_moment << d["I_xx"], d["I_xy"], d["I_xz"],
                      d["I_xy"], d["I_yy"], d["I_yz"],
                      d["I_xz"], d["I_yz"], d["I_zz"];

    Eigen::EigenSolver<Matrix3d> solver(inertia_moment);

    // eigens are real since inertia moment is symmetric
    ArrayXd evals = solver.eigenvalues().real();
    ArrayXXd evecs = solver.eigenvectors().real().transpose();

    d["I_values"] = {evals(0), evals(1), evals(2)};

    auto tmp = Json::array();

    for (int i = 0; i != 3; ++i)
    {
      RowArrayXd evec = evecs.row(i);
      tmp.push_back({evec(0), evec(1), evec(2)});
    }

    d["I_vectors"].swap(tmp);

    // compute molecular orientation

    int index;
    evals.minCoeff(&index);

    RowArrayXd orientation = evecs.row(index).square().unaryExpr(
      [](double x)
      {
        return 0.5 * (3.0*x - 1.0);
      });

    d["S_x"] = orientation(0);
    d["S_y"] = orientation(1);
    d["S_z"] = orientation(2);
  }

  datakeys.add({"I_values", "I_vectors", "S_x", "S_y", "S_z"});
}

/* ------------------------------------------------------------------ */
