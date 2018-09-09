/*!
  @file src/alias/eigen.h
  @brief ...
  @author Takayuki Kobayashi
  @date 2018/09/09
  @details ...
*/

#ifndef ALIAS_EIGEN_H
#define ALIAS_EIGEN_H

#include <Eigen/LU>

/* NOTE:
  Eigen::Array is column major by default. But, in this project,
  Eigen::Array is row major to be compatible with NumPy.
*/

/*!
  @brief ...
*/
using ArrayXXi
  = Eigen::Array<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
/*!
  @brief ...
*/
using ArrayXXd
  = Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
/*!
  @brief ...
*/
using ArrayXi
  = Eigen::Array<int, Eigen::Dynamic, 1>;
/*!
  @brief ...
*/
using ArrayXd
  = Eigen::Array<double, Eigen::Dynamic, 1>;
/*!
  @brief ...
*/
using RowArrayXi
  = Eigen::Array<int, 1, Eigen::Dynamic>;
/*!
  @brief ...
*/
using RowArrayXd
  = Eigen::Array<double, 1, Eigen::Dynamic>;
/*!
  @brief ...
*/
using MatrixXi = Eigen::MatrixXi;
/*!
  @brief ...
*/
using MatrixXd = Eigen::MatrixXd;
/*!
  @brief ...
*/
using VectorXi = Eigen::VectorXi;
/*!
  @brief ...
*/
using VectorXd = Eigen::VectorXd;
/*!
  @brief ...
*/
using RowVectorXi = Eigen::RowVectorXi;
/*!
  @brief ...
*/
using RowVectorXd = Eigen::RowVectorXd;
/*!
  @brief ...
*/
using Matrix3i = Eigen::Matrix3i;
/*!
  @brief ...
*/
using Matrix3d = Eigen::Matrix3d;
/*!
  @brief ...
*/
using Vector3i = Eigen::Vector3i;
/*!
  @brief ...
*/
using Vector3d = Eigen::Vector3d;
/*!
  @brief ...
*/
using RowVector3i = Eigen::RowVector3i;
/*!
  @brief ...
*/
using RowVector3d = Eigen::RowVector3d;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_eigen.h>
#endif

#endif