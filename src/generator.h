/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <map>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

class Generator {
 public:
  Generator() = default;
  virtual ~Generator() = default;
  void appoint();
  void cancel();
  void goodbye();
  void clockout();
  const nlohmann::json &get_data();
  // function for reference use from Python
  const pybind11::object get_data_py();
 protected:
  bool data_exists = false;
  int n_appointment = 0;
  std::string dataname;
  nlohmann::json data;
  void check_data();
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
 protected:
  void generate() override {
    PYBIND11_OVERLOAD_PURE(void, GEN, generate, );
  }
};

static void pybind_generator(py::module &m) {

  py::class_<Generator,PyGenerator<>,std::shared_ptr<Generator>>(m, "Generator")
    .def(py::init<>())
    .def("get_data", &Generator::get_data_py);

}

#endif
