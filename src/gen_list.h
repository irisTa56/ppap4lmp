/* ---------------------------------------------------------------------
GenList: stands for Generator List containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_LIST_H
#define GEN_LIST_H

#include "generator.h"

class GenList : public Generator {
  std::vector<std::shared_ptr<Generator>> generator_list;
 public:
  GenList(std::vector<std::shared_ptr<Generator>>);
  virtual ~GenList() = default;
  virtual const nlohmann::json &get_data() override;
  virtual std::shared_ptr<Generator> get_generator(int);
  const int get_length();
};

/* ------------------------------------------------------------------ */
// for pybind11

// trampoline class to bind Python
class PyGenList : public GenList {
 public:
  using GenList::GenList;
  const nlohmann::json &get_data() override
  {
    PYBIND11_OVERLOAD_PURE(const nlohmann::json &, GenList, get_data, );
  }
  std::shared_ptr<Generator> get_generator(int index) override
  {
    PYBIND11_OVERLOAD(
      std::shared_ptr<Generator>, GenList, get_generator, index);
  }
  const bool check_key(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(const bool, GenList, check_key, key);
  }
  const std::vector<bool> check_keys(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(const std::vector<bool>, GenList, check_keys, keys);
  }
  const Eigen::VectorXi get_int_vector(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(const Eigen::VectorXi, GenList, get_int_vector, key);
  }
  const Eigen::VectorXd get_double_vector(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(const Eigen::VectorXd, GenList, get_double_vector, key);
  }
  const Eigen::ArrayXXi get_int_array(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(const Eigen::ArrayXXi, GenList, get_int_array, keys);
  }
  const Eigen::ArrayXXd get_double_array(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(const Eigen::ArrayXXd, GenList, get_double_array, keys);
  }
};

static void pybind_gen_list(py::module &m)
{
  py::class_<GenList,PyGenList,Generator,std::shared_ptr<GenList>>(m, "GenList")
    .def(py::init<std::vector<std::shared_ptr<Generator>>>())
    .def("get_length", &GenList::get_length);
}

#endif
