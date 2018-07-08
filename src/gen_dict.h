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
  virtual const json &get_data() override;
  virtual std::shared_ptr<Generator> get_generator(const std::string &);
  const std::unordered_set<std::string> get_keys();
};

/* ------------------------------------------------------------------ */
// for pybind11

// trampoline class to bind Python
class PyGenDict : public GenDict {
 public:
  using GenDict::GenDict;
  const json &get_data() override
  {
    PYBIND11_OVERLOAD_PURE(const json &, GenDict, get_data, );
  }
  std::shared_ptr<Generator> get_generator(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(
      std::shared_ptr<Generator>, GenDict, get_generator, key);
  }
  Eigen::ArrayXi get_1d_int(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(Eigen::ArrayXi, GenDict, get_1d_int, key);
  }
  Eigen::ArrayXd get_1d_double(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(Eigen::ArrayXd, GenDict, get_1d_double, key);
  }
  Eigen::ArrayXXi get_2d_int(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(Eigen::ArrayXXi, GenDict, get_2d_int, keys);
  }
  Eigen::ArrayXXd get_2d_double(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(Eigen::ArrayXXd, GenDict, get_2d_double, keys);
  }
};

static void pybind_gen_dict(py::module &m)
{
  py::class_<GenDict,PyGenDict,Generator,std::shared_ptr<GenDict>>(m, "GenDict")
    .def(py::init<std::unordered_set<std::shared_ptr<Generator>>>())
    .def("get_keys", &GenDict::get_keys);
}

#endif
