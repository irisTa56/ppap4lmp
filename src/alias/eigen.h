/*!
  @file src/alias/eigen.h
  @brief This file includes \e Eigen and defines some aliases for the
  Eigen-Vector, Matrix and Array.
  @author Takayuki Kobayashi
  @date 2018/09/09
*/

#ifndef ALIAS_EIGEN_H
#define ALIAS_EIGEN_H

#include <Eigen/LU>

/*!
  @brief \e ArrayXXi is an alias for two-dimensional array of Eigen
  where the values are integer.
  @details Eigen-Array is column major by default. But, in this
  program, row major is preferable so that the array can be passed to
  Python as Numpy-Array, which is row major, without confusing.
*/
using ArrayXXi
  = Eigen::Array<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
/*!
  @brief \e ArrayXXd is an alias for two-dimensional array of Eigen
  where the values are double.
  @details Eigen-Array is column major by default. But, in this
  program, row major is preferable so that the array can be passed to
  Python as Numpy-Array, which is row major, without confusing.
*/
using ArrayXXd
  = Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
/*!
  @brief \e ArrayXi is an alias for column array of Eigen where the
  values are integer.
*/
using ArrayXi
  = Eigen::Array<int, Eigen::Dynamic, 1>;
/*!
  @brief \e ArrayXd is an alias for column array of Eigen where the
  values are double.
*/
using ArrayXd
  = Eigen::Array<double, Eigen::Dynamic, 1>;
/*!
  @brief \e RowArrayXi is an alias for row array of Eigen where the
  values are integer.
*/
using RowArrayXi
  = Eigen::Array<int, 1, Eigen::Dynamic>;
/*!
  @brief \e RowArrayXd is an alias for row array of Eigen where the
  values are double.
*/
using RowArrayXd
  = Eigen::Array<double, 1, Eigen::Dynamic>;
/*!
  @brief \e MatrixXi is an alias for arbitrary square matrix of Eigen
  where the values are integer.
*/
using MatrixXi = Eigen::MatrixXi;
/*!
  @brief \e MatrixXd is an alias for arbitrary square matrix of Eigen
  where the values are double.
*/
using MatrixXd = Eigen::MatrixXd;
/*!
  @brief \e VectorXi is an alias for column vector of arbitrary length
  of Eigen where the values are integer.
*/
using VectorXi = Eigen::VectorXi;
/*!
  @brief \e VectorXd is an alias for column vector of arbitrary length
  of Eigen where the values are double.
*/
using VectorXd = Eigen::VectorXd;
/*!
  @brief \e RowVectorXi is an alias for row vector of arbitrary length of
  Eigen where the values are integer.
*/
using RowVectorXi = Eigen::RowVectorXi;
/*!
  @brief \e RowVectorXd is an alias for row vector of arbitrary length of
  Eigen where the values are double.
*/
using RowVectorXd = Eigen::RowVectorXd;
/*!
  @brief \e Matrix3i is an alias for square matrix of order 3 of Eigen
  where the values are integer.
*/
using Matrix3i = Eigen::Matrix3i;
/*!
  @brief \e Matrix3d is an alias for square matrix of order 3 of Eigen
  where the values are double.
*/
using Matrix3d = Eigen::Matrix3d;
/*!
  @brief \e Vector3i is an alias for 3-elements column vector of Eigen
  where the values are integer.
*/
using Vector3i = Eigen::Vector3i;
/*!
  @brief \e Vector3d is an alias for 3-elements column vector of Eigen
  where the values are double.
*/
using Vector3d = Eigen::Vector3d;
/*!
  @brief \e RowVector3i is an alias for 3-elements row vector of Eigen
  where the values are integer.
*/
using RowVector3i = Eigen::RowVector3i;
/*!
  @brief \e RowVector3d is an alias for 3-elements row vector of Eigen
  where the values are double.
*/
using RowVector3d = Eigen::RowVector3d;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_eigen.h>
#endif

#endif