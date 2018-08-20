/* ---------------------------------------------------------------------
AddMolecularOrientation: stands for Adder for Molecular Orientation.

create: 2018/07/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <Eigen/Eigenvalues>

#include "add_molecular_orientation.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void AddMolecularOrientation::compute_impl(
  Json &data, Set<Str> &datakeys)
{
  if (!check_containment<Str>(
    datakeys, {"I_xx", "I_yy", "I_zz", "I_xy", "I_yz", "I_zx"}))
  {
    runtime_error(
      "AddMolecularOrientation needs 'I_**' "
      "(xx/yy/zz/xy/yz/zx)");
    return;
  }

  for (auto &d : data)
  {
    // compute principal values and vectors

    MatrixXd inertia_moment(3, 3);
    inertia_moment << d["I_xx"], d["I_xy"], d["I_zx"],
                      d["I_xy"], d["I_yy"], d["I_yz"],
                      d["I_zx"], d["I_yz"], d["I_zz"];

    Eigen::EigenSolver<MatrixXd> solver(inertia_moment);

    // eigens are real since inertia moment is symmetric
    ArrayXd evals = solver.eigenvalues().real();
    ArrayXXd evecs = solver.eigenvectors().real().transpose();

    d["I_values"] = {evals(0), evals(1), evals(2)};
    d["I_vectors"].clear();

    for (int i = 0; i != 3; ++i)
    {
      RowArrayXd evec = evecs.row(i);
      d["I_vectors"].push_back({evec(0), evec(1), evec(2)});
    }

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

  datakeys.insert({"I_values", "I_vectors", "S_x", "S_y", "S_z"});
}
