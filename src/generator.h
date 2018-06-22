/* ---------------------------------------------------------------------
This file is for Generator class.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>

#include <nlohmann/json.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/cast.h>

class Generator {
 public:
  Generator() = default;
  virtual ~Generator() = default;
  void appoint();
  void cancel();
  void goodbye();
  nlohmann::json &get_data();
  pybind11::object get_data_py();
 protected:
  std::string dataname;
  // functions & variables
  virtual void generate() = 0;
  virtual void filter() {};  // for array data
  void check_data();
  bool data_exists = false;
  int n_appointment = 0;
  nlohmann::json data;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class GEN = Generator>
class PyGenerator : public GEN {
 public:
  using GEN::GEN;
 protected:
  void generate() override {
    PYBIND11_OVERLOAD_PURE(void, GEN, generate, );
  }
  void filter() override {
    PYBIND11_OVERLOAD(void, GEN, filter, );
  }
};

static void pybind_generator(py::module &m) {

  py::class_<Generator, PyGenerator<>>(m, "Generator")
    .def(py::init<>())
    .def("get_data", &Generator::get_data_py);

}

#endif
