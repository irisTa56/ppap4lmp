/* ---------------------------------------------------------------------
Modifier: is an abstract class to modify (e.g. add new properties to)
data.

create: 2018/06/24 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef MODIFIER_H
#define MODIFIER_H

#include <map>
#include <memory>
#include <vector>

#include "json_caster.h"

class Modifier {
 public:
  Modifier() = default;
  virtual ~Modifier() = default;
  virtual void modify(nlohmann::json &data) = 0;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class MOD = Modifier>
class PyModifier : public MOD {
 public:
  using MOD::MOD;
  void modify(nlohmann::json &data) override {
    PYBIND11_OVERLOAD_PURE(void, MOD, modify, data);
  }
};

static void pybind_modifier(py::module &m) {

  py::class_<Modifier,PyModifier<>,std::shared_ptr<Modifier>>(m, "Modifier")
    .def(py::init<>());

}

#endif