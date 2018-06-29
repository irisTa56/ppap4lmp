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
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

#include "json_caster.h"

class Generator : public std::enable_shared_from_this<Generator> {
 public:
  Generator() = default;
  virtual ~Generator() = default;
  virtual void appoint();
  virtual void goodbye();
  const std::string &get_classname();
  const std::string &get_dataname();
  // function for dict/list generators
  virtual std::shared_ptr<Generator> get_generator();
  // function for leaf (normal) generators
  void set_parser(std::shared_ptr<class Updater>);
  void append_adder(std::shared_ptr<class Updater>);
  const nlohmann::json &get_data();
  const bool check_key(const std::string &);
  const std::vector<bool> check_keys(const std::vector<std::string> &);
  // function for generators with array data
  const Eigen::VectorXi get_int_vector(const std::string &);
  const Eigen::VectorXd get_double_vector(const std::string &);
  const Eigen::ArrayXXi get_int_array(const std::vector<std::string> &);
  const Eigen::ArrayXXd get_double_array(const std::vector<std::string> &);
 protected:
  std::string classname;
  std::string dataname;
  nlohmann::json data = nullptr;
  void check_data();
 private:
  int n_appointment = 0;
  std::vector<std::shared_ptr<class Updater>> updaters;
  std::vector<std::shared_ptr<Generator>> sub_generators;
  void check_keys_one(
    std::unordered_map<std::string,int> &, const nlohmann::json &);
};

#include "updater.h"

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
  std::shared_ptr<Generator> get_generator() override
  {
    PYBIND11_OVERLOAD(std::shared_ptr<Generator>, GEN, get_generator, );
  }
};

static void pybind_generator(py::module &m)
{
  py::class_<Generator,PyGenerator<>,std::shared_ptr<Generator>>(m, "Generator")
    .def(py::init<>())
    .def("set_parser", &Generator::set_parser)
    .def("append_adder", &Generator::append_adder)
    .def("check_key", &Generator::check_key)
    .def("check_keys", &Generator::check_keys)
    .def("get_data", &Generator::get_data,
      py::return_value_policy::reference_internal)
    .def("get_int_vector", &Generator::get_int_vector)
    .def("get_double_vector", &Generator::get_double_vector)
    .def("get_int_array", &Generator::get_int_array)
    .def("get_double_array", &Generator::get_double_array);
}

#endif
