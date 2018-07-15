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

#include <omp.h>

#include <pybind11/stl.h>

#include "eigen_aliases.h"
#include "json_caster.h"

class Generator;
class Updater;

using UpdatePair
  = std::pair<std::shared_ptr<Generator>,std::shared_ptr<Updater>>;

class Generator : public std::enable_shared_from_this<Generator> {
  omp_lock_t omp_lock;
  int n_remain = 0;
 protected:
  static int instance_count;
  std::string datatype;
  std::string dataname;
  json data = nullptr;
  std::vector<UpdatePair> update_chain;
  void increment_remain();
  void decrement_remain();
  void update_data(std::shared_ptr<Updater>);
  void merge_update_chain(const std::vector<UpdatePair> &);
 public:
  Generator() { omp_init_lock(&omp_lock); }
  virtual ~Generator() = default;
  virtual const json &get_data() = 0;
  virtual std::shared_ptr<Generator> get_generator();
  virtual std::shared_ptr<Generator> get_generator(int);
  virtual std::shared_ptr<Generator> get_generator(const std::string &);
  virtual ArrayXi get_1d_int(const std::string &);
  virtual ArrayXd get_1d_double(const std::string &);
  virtual ArrayXXi get_2d_int(const std::vector<std::string> &);
  virtual ArrayXXd get_2d_double(const std::vector<std::string> &);
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
  const json &get_data() override
  {
    PYBIND11_OVERLOAD_PURE(const json &, GEN, get_data, );
  }
  std::shared_ptr<Generator> get_generator() override
  {
    PYBIND11_OVERLOAD(
      std::shared_ptr<Generator>, GEN, get_generator, );
  }
  std::shared_ptr<Generator> get_generator(
    int index) override
  {
    PYBIND11_OVERLOAD(
      std::shared_ptr<Generator>, GEN, get_generator, index);
  }
  std::shared_ptr<Generator> get_generator(
    const std::string &key) override
  {
    PYBIND11_OVERLOAD(
      std::shared_ptr<Generator>, GEN, get_generator, key);
  }
  ArrayXi get_1d_int(const std::string &key) override
  {
    PYBIND11_OVERLOAD(ArrayXi, GEN, get_1d_int, key);
  }
  ArrayXd get_1d_double(const std::string &key) override
  {
    PYBIND11_OVERLOAD(ArrayXd, GEN, get_1d_double, key);
  }
  ArrayXXi get_2d_int(const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(ArrayXXi, GEN, get_2d_int, keys);
  }
  ArrayXXd get_2d_double(const std::vector<std::string> &keys) override
  {
    PYBIND11_OVERLOAD(ArrayXXd, GEN, get_2d_double, keys);
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
