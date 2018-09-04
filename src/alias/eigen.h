#ifndef ALIAS_EIGEN_H
#define ALIAS_EIGEN_H

#include <Eigen/LU>

/* NOTE:
  Eigen::Array is column major by default. But, in this project,
  Eigen::Array is row major to be compatible with NumPy.
*/

using ArrayXXi
  = Eigen::Array<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using ArrayXXd
  = Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

using ArrayXi
  = Eigen::Array<int, Eigen::Dynamic, 1>;
using ArrayXd
  = Eigen::Array<double, Eigen::Dynamic, 1>;

using RowArrayXi
  = Eigen::Array<int, 1, Eigen::Dynamic>;
using RowArrayXd
  = Eigen::Array<double, 1, Eigen::Dynamic>;

using MatrixXi = Eigen::MatrixXi;
using MatrixXd = Eigen::MatrixXd;

using VectorXi = Eigen::VectorXi;
using VectorXd = Eigen::VectorXd;

using RowVectorXi = Eigen::RowVectorXi;
using RowVectorXd = Eigen::RowVectorXd;

using Matrix3i = Eigen::Matrix3i;
using Matrix3d = Eigen::Matrix3d;

using Vector3i = Eigen::Vector3i;
using Vector3d = Eigen::Vector3d;

using RowVector3i = Eigen::RowVector3i;
using RowVector3d = Eigen::RowVector3d;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_eigen.h>
#endif

#endif