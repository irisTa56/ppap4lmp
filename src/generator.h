/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <Eigen/LU>
#include <omp.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

#include "json_caster.h"

class Generator;
class Updater;

using UpdatePair
  = std::pair<std::shared_ptr<Generator>,std::shared_ptr<Updater>>;
using Map2Index = std::unordered_map<nlohmann::json,int>;

class Generator : public std::enable_shared_from_this<Generator> {
  omp_lock_t omp_lock;
  int n_remain = 0;
 protected:
  static int instance_count;
  std::string datatype;
  std::string dataname;
  nlohmann::json data = nullptr;
  std::vector<UpdatePair> update_chain;
  void increment_remain();
  void decrement_remain();
  void update_data(std::shared_ptr<Updater>);
  void merge_update_chain(const std::vector<UpdatePair> &);
 public:
  Generator() { omp_init_lock(&omp_lock); }
  virtual ~Generator() = default;
  virtual const nlohmann::json &get_data() = 0;
  virtual std::shared_ptr<Generator> get_generator();
  virtual const bool check_key(
    const std::string &);
  virtual const std::vector<bool> check_keys(
    const std::vector<std::string> &);
  virtual const Eigen::VectorXi get_int_vector(
    const std::string &);
  virtual const Eigen::VectorXd get_double_vector(
    const std::string &);
  virtual const Eigen::ArrayXXi get_int_array(
    const std::vector<std::string> &);
  virtual const Eigen::ArrayXXd get_double_array(
    const std::vector<std::string> &);
  virtual const Map2Index &get_map_to_index(const nlohmann::json &);
  void appoint();
  void hello();
  void goodbye();
  const std::string &get_datatype();
  const std::string &get_dataname();
  const std::vector<UpdatePair> &get_update_chain();
};

#include "updater.h"

/* ------------------------------------------------------------------ */
// for pybind11

// trampoline class to bind Python
template <class GEN = Generator>
class PyGenerator : public GEN {
 public:
  using GEN::GEN;
  const nlohmann::json &get_data() override
  {
    PYBIND11_OVERLOAD_PURE(const nlohmann::json &, GEN, get_data, );
  }
  std::shared_ptr<Generator> get_generator() override
  {
    PYBIND11_OVERLOAD(
      std::shared_ptr<Generator>, GEN, get_generator, );
  }
  const bool check_key(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(const bool, GEN, check_key, key);
  }
  const std::vector<bool> check_keys(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(const std::vector<bool>, GEN, check_keys, keys);
  }
  const Eigen::VectorXi get_int_vector(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(const Eigen::VectorXi, GEN, get_int_vector, key);
  }
  const Eigen::VectorXd get_double_vector(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(const Eigen::VectorXd, GEN, get_double_vector, key);
  }
  const Eigen::ArrayXXi get_int_array(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(const Eigen::ArrayXXi, GEN, get_int_array, keys);
  }
  const Eigen::ArrayXXd get_double_array(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(const Eigen::ArrayXXd, GEN, get_double_array, keys);
  }
  const Map2Index &get_map_to_index(const nlohmann::json &keys) override
  {
    PYBIND11_OVERLOAD(const Map2Index &, GEN, get_map_to_index, keys);
  }
};

static void pybind_generator(py::module &m)
{
  py::class_<Generator,PyGenerator<>,std::shared_ptr<Generator>>(m, "Generator")
    .def(py::init<>())
    .def("get_datatype", &Generator::get_datatype)
    .def("get_dataname", &Generator::get_dataname);
}

#endif
