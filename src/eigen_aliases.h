#include <Eigen/LU>

#include <pybind11/eigen.h>

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
