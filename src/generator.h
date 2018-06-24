/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <map>
#include <vector>

#include "json_caster.h"

class Generator {
 public:
  Generator() = default;
  virtual ~Generator() = default;
  virtual void appoint();
  virtual void cancel();
  virtual void goodbye();
  virtual void clockout();
  virtual const nlohmann::json &get_data();
 protected:
  bool data_exists = false;
  int n_appointment = 0;
  std::string dataname;
  nlohmann::json data;
  std::vector<std::shared_ptr<class Modifier>> modifiers;
  virtual void check_data();
  virtual int count_keys(
    const std::vector<std::string> &keys, bool check_only_front = true);
  virtual void generate() = 0;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class GEN = Generator>
class PyGenerator : public GEN {
 public:
  using GEN::GEN;
  void appoint() override {
    PYBIND11_OVERLOAD(void, GEN, appoint, );
  }
  void cancel() override {
    PYBIND11_OVERLOAD(void, GEN, cancel, );
  }
  void goodbye() override {
    PYBIND11_OVERLOAD(void, GEN, goodbye, );
  }
  void clockout() override {
    PYBIND11_OVERLOAD(void, GEN, clockout, );
  }
  const nlohmann::json &get_data() override {
    PYBIND11_OVERLOAD(const nlohmann::json &, GEN, get_data, );
  }
 protected:
  void check_data() override {
    PYBIND11_OVERLOAD(void, GEN, check_data, );
  }
  int count_keys(
    const std::vector<std::string> &keys, bool check_only_front = true) override {
    PYBIND11_OVERLOAD(int, GEN, count_keys, keys, check_only_front);
  }
  void generate() override {
    PYBIND11_OVERLOAD_PURE(void, GEN, generate, );
  }
};

static void pybind_generator(py::module &m) {

  py::class_<Generator,PyGenerator<>,std::shared_ptr<Generator>>(m, "Generator")
    .def(py::init<>())
    .def("get_data", &Generator::get_data);

}

#endif
