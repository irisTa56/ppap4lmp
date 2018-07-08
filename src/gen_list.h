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
  virtual const json &get_data() override;
  virtual std::shared_ptr<Generator> get_generator(int);
  const int get_length();
};

/* ------------------------------------------------------------------ */
// for pybind11

// trampoline class to bind Python
class PyGenList : public GenList {
 public:
  using GenList::GenList;
  const json &get_data() override
  {
    PYBIND11_OVERLOAD_PURE(const json &, GenList, get_data, );
  }
  std::shared_ptr<Generator> get_generator(int index) override
  {
    PYBIND11_OVERLOAD(
      std::shared_ptr<Generator>, GenList, get_generator, index);
  }
  Eigen::ArrayXi get_1d_int(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(Eigen::ArrayXi, GenList, get_1d_int, key);
  }
  Eigen::ArrayXd get_1d_double(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(Eigen::ArrayXd, GenList, get_1d_double, key);
  }
  Eigen::ArrayXXi get_2d_int(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(Eigen::ArrayXXi, GenList, get_2d_int, keys);
  }
  Eigen::ArrayXXd get_2d_double(
    const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(Eigen::ArrayXXd, GenList, get_2d_double, keys);
  }
};

static void pybind_gen_list(py::module &m)
{
  py::class_<GenList,PyGenList,Generator,std::shared_ptr<GenList>>(m, "GenList")
    .def(py::init<std::vector<std::shared_ptr<Generator>>>())
    .def("get_length", &GenList::get_length);
}

#endif
