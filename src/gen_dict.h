/* ---------------------------------------------------------------------
GenDict: stands for Generator Dictionary containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_DICT_H
#define GEN_DICT_H

#include "generator.h"

class GenDict : public Generator {
  std::unordered_map<std::string,std::shared_ptr<Generator>> generator_dict;
 public:
  GenDict(std::unordered_set<std::shared_ptr<Generator>>);
  virtual ~GenDict() = default;
  virtual const nlohmann::json &get_data() override;
  virtual std::shared_ptr<Generator> get_generator(const std::string &);
  const std::unordered_set<std::string> get_keys();
};

/* ------------------------------------------------------------------ */
// for pybind11

// trampoline class to bind Python
class PyGenDict : public GenDict {
 public:
  using GenDict::GenDict;
  const nlohmann::json &get_data() override
  {
    PYBIND11_OVERLOAD_PURE(const nlohmann::json &, GenDict, get_data, );
  }
  std::shared_ptr<Generator> get_generator(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(
      std::shared_ptr<Generator>, GenDict, get_generator, key);
  }
  const bool check_key(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(const bool, GenDict, check_key, key);
  }
  const std::vector<bool> check_keys(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(const std::vector<bool>, GenDict, check_keys, keys);
  }
  const Eigen::VectorXi get_int_vector(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(const Eigen::VectorXi, GenDict, get_int_vector, key);
  }
  const Eigen::VectorXd get_double_vector(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(const Eigen::VectorXd, GenDict, get_double_vector, key);
  }
  const Eigen::ArrayXXi get_int_array(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(const Eigen::ArrayXXi, GenDict, get_int_array, keys);
  }
  const Eigen::ArrayXXd get_double_array(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(const Eigen::ArrayXXd, GenDict, get_double_array, keys);
  }
};

static void pybind_gen_dict(py::module &m)
{
  py::class_<GenDict,PyGenDict,Generator,std::shared_ptr<GenDict>>(m, "GenDict")
    .def(py::init<std::unordered_set<std::shared_ptr<Generator>>>())
    .def("get_keys", &GenDict::get_keys);
}

#endif
