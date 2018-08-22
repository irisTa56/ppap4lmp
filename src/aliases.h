#ifndef ALIASES_H
#define ALIASES_H

#include <memory>

template <typename T>
using ShPtr = std::shared_ptr<T>;

#include <string>

using Str = std::string;

#include <vector>

template <typename T>
using List = std::vector<T>;

#include <unordered_map>

template <typename T, typename U>
using Dict = std::unordered_map<T,U>;

#include <unordered_set>

template <typename T>
using Set = std::unordered_set<T>;

#include <Eigen/LU>

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

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "json_caster.h"

template <typename T>
using EnShThis = std::enable_shared_from_this<T>;

#endif