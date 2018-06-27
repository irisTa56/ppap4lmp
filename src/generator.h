/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GENERATOR_H
#define GENERATOR_H

#include "adder.h"

class Generator {
 public:
  Generator() = default;
  virtual ~Generator() = default;
  virtual void appoint();
  virtual void goodbye();
  virtual const std::vector<int> count_keys(
    const std::vector<std::string> &keys, bool check_only_front = true);
  virtual const nlohmann::json &get_data();
  void append_adder(std::shared_ptr<Adder>);
 protected:
  int n_appointment = 0;
  std::string dataname;
  nlohmann::json data = nullptr;
  std::vector<std::shared_ptr<Adder>> adders;
  virtual void generate() = 0;
  virtual void check_data();
 private:
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
  const std::vector<int> count_keys(
    const std::vector<std::string> &keys,
    bool check_only_front = true) override
  {
    PYBIND11_OVERLOAD(
      const std::vector<int>, GEN, count_keys, keys, check_only_front);
  }
  const nlohmann::json &get_data() override
  {
    PYBIND11_OVERLOAD(const nlohmann::json &, GEN, get_data, );
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
    .def("count_keys", &Generator::count_keys,
      py::arg("keys"), py::arg("check_only_front") = true)
    .def("get_data", &Generator::get_data,
      py::return_value_policy::reference_internal)
    .def("append_adder", &Generator::append_adder);;
}

#endif
