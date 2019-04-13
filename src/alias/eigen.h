/*!
  @file src/alias/eigen.h
  @brief This file includes *Eigen* and defines some aliases for the
  Eigen-Vector, Matrix and Array.
  @author Takayuki Kobayashi
  @date 2018/09/09
*/

#ifndef ALIAS_EIGEN_H
#define ALIAS_EIGEN_H

#include <Eigen/Dense>

/*!
  @brief *ArrayXXi* is an alias for a two-dimensional integer array.

  In the Eigen library, *ArrayXXi* is column major by default.
  In this program, however, row major is preferable so that the array
  can be passed to Python as Numpy-array, which is row major.
*/
using ArrayXXi
  = Eigen::Array<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
/*!
  @brief *ArrayXXd* is an alias for a two-dimensional array
  of float numbers.

  In the Eigen library, *ArrayXXd* is column major by default.
  In this program, however, row major is preferable so that the array
  can be passed to Python as Numpy-array, which is row major.
*/
using ArrayXXd
  = Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
/*!
  @brief *ArrayXi* is an alias for a column array of integers.
*/
using ArrayXi
  = Eigen::Array<int, Eigen::Dynamic, 1>;
/*!
  @brief *ArrayXd* is an alias for a column array of float numbers.
*/
using ArrayXd
  = Eigen::Array<double, Eigen::Dynamic, 1>;
/*!
  @brief *RowArrayXi* is an alias for a row array of integers.
*/
using RowArrayXi
  = Eigen::Array<int, 1, Eigen::Dynamic>;
/*!
  @brief *RowArrayXd* is an alias for a row array of float numbers.
*/
using RowArrayXd
  = Eigen::Array<double, 1, Eigen::Dynamic>;
/*!
  @brief *MatrixXi* is an alias for an arbitrary square matrix
  of integers.
*/
using MatrixXi = Eigen::MatrixXi;
/*!
  @brief *MatrixXd* is an alias for an arbitrary square matrix
  of float numbers.
*/
using MatrixXd = Eigen::MatrixXd;
/*!
  @brief *VectorXi* is an alias for a column vector of integers
  with arbitrary length.
*/
using VectorXi = Eigen::VectorXi;
/*!
  @brief *VectorXd* is an alias for a column vector of float numbers
  with arbitrary length.
*/
using VectorXd = Eigen::VectorXd;
/*!
  @brief *RowVectorXi* is an alias for a row vector of integers
  with arbitrary length.
*/
using RowVectorXi = Eigen::RowVectorXi;
/*!
  @brief *RowVectorXd* is an alias for a row vector of float numbers
  with arbitrary length.
*/
using RowVectorXd = Eigen::RowVectorXd;
/*!
  @brief *Matrix3i* is an alias for a 3x3 matrix of integers.
*/
using Matrix3i = Eigen::Matrix3i;
/*!
  @brief *Matrix3d* is an alias for a 3x3 matrix of float numbers.
*/
using Matrix3d = Eigen::Matrix3d;
/*!
  @brief *Vector3i* is an alias for a 3-elements column vector
  of integers.
*/
using Vector3i = Eigen::Vector3i;
/*!
  @brief *Vector3d* is an alias for a 3-elements column vector
  of float numbers.
*/
using Vector3d = Eigen::Vector3d;
/*!
  @brief *RowVector3i* is an alias for a 3-elements row vector
  of integers.
*/
using RowVector3i = Eigen::RowVector3i;
/*!
  @brief *RowVector3d* is an alias for a 3-elements row vector
  of Eigen float numbers.
*/
using RowVector3d = Eigen::RowVector3d;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_eigen.h>
#endif

#endif