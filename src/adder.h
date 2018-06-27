/* ---------------------------------------------------------------------
Adder: is an abstract class to add new properties to data in Generator.

create: 2018/06/26 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADDER_H
#define ADDER_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "json_caster.h"

class Adder {
 public:
  Adder() = default;
  virtual ~Adder() = default;
  void compute(nlohmann::json &, const std::string &);
 protected:
  virtual void compute_impl(nlohmann::json &data) = 0;
 private:
  std::unordered_set<std::string> dataname_blacklist;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class ADD = Adder>
class PyAdder : public ADD {
 public:
  using ADD::ADD;
 protected:
  void compute_impl(nlohmann::json &data) override
  {
    PYBIND11_OVERLOAD_PURE(void, ADD, compute_impl, data);
  }
};

static void pybind_adder(py::module &m)
{
  py::class_<Adder,PyAdder<>,std::shared_ptr<Adder>>(m, "Adder")
    .def(py::init<>());
}

#endif