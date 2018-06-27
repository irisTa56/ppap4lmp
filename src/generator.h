/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <pybind11/eigen.h>
#include <Eigen/LU>

#include "adder.h"

class Generator {
 public:
  Generator() = default;
  virtual ~Generator() = default;
  virtual void appoint();
  virtual void goodbye();
  virtual void append_adder(std::shared_ptr<Adder> add);
  virtual const nlohmann::json &get_data();
  virtual const Eigen::VectorXi get_int_vector(
    const std::string &key);
  virtual const Eigen::VectorXd get_double_vector(
    const std::string &key);
  virtual const Eigen::ArrayXXi get_int_array(
    const std::vector<std::string> &keys);
  virtual const Eigen::ArrayXXd get_double_array(
    const std::vector<std::string> &keys);
  virtual const std::vector<bool> check_keys(
    const std::vector<std::string> &keys);
  virtual const std::vector<int> count_keys(
    const std::vector<std::string> &keys);
 protected:
  int n_appointment = 0;
  std::string dataname;
  nlohmann::json data = nullptr;
  std::vector<std::shared_ptr<Adder>> adders;
  virtual void generate() = 0;
  virtual void check_data();
 private:
  void check_keys_one(
    std::unordered_map<std::string,int> &, const nlohmann::json &);
  void count_keys_one(
    std::unordered_map<std::string,int> &, const nlohmann::json &);
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class GEN = Generator>
class PyGenerator : public GEN {
 public:
  using GEN::GEN;
  void appoint() override
  {
    PYBIND11_OVERLOAD(void, GEN, appoint, );
  }
  void goodbye() override
  {
    PYBIND11_OVERLOAD(void, GEN, goodbye, );
  }
  void append_adder(std::shared_ptr<Adder> add) override
  {
    PYBIND11_OVERLOAD(void, GEN, append_adder, add);
  }
  const nlohmann::json &get_data() override
  {
    PYBIND11_OVERLOAD(const nlohmann::json &, GEN, get_data, );
  }
  const Eigen::VectorXi get_int_vector(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(
      const Eigen::VectorXi, GEN, get_int_vector, key);
  }
  const Eigen::VectorXd get_double_vector(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(
      const Eigen::VectorXd, GEN, get_double_vector, key);
  }
  const Eigen::ArrayXXi get_int_array(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(
      const Eigen::ArrayXXi, GEN, get_int_array, keys);
  }
  const Eigen::ArrayXXd get_double_array(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(
      const Eigen::ArrayXXd, GEN, get_double_array, keys);
  }
  const std::vector<bool> check_keys(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(
      const std::vector<bool>, GEN, check_keys, keys);
  }
  const std::vector<int> count_keys(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(
      const std::vector<int>, GEN, count_keys, keys);
  }
 protected:
  void check_data() override
  {
    PYBIND11_OVERLOAD(void, GEN, check_data, );
  }
  void generate() override
  {
    PYBIND11_OVERLOAD_PURE(void, GEN, generate, );
  }
};

static void pybind_generator(py::module &m)
{
  py::class_<Generator,PyGenerator<>,std::shared_ptr<Generator>>(m, "Generator")
    .def(py::init<>())
    .def("check_keys", &Generator::check_keys)
    .def("count_keys", &Generator::count_keys)
    .def("get_data", &Generator::get_data,
      py::return_value_policy::reference_internal)
    .def("get_int_vector", &Generator::get_int_vector)
    .def("get_double_vector", &Generator::get_double_vector)
    .def("get_int_array", &Generator::get_int_array)
    .def("get_double_array", &Generator::get_double_array)
    .def("append_adder", &Generator::append_adder);;
}

#endif
