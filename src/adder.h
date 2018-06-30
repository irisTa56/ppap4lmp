/* ---------------------------------------------------------------------
Adder: is an abstract class to add new properties to data in Generator.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADDER_H
#define ADDER_H

#include "updater.h"

class Adder : public Updater {
 public:
  Adder() = default;
  virtual ~Adder() = default;
  virtual void compute(nlohmann::json &) override;
 private:
  bool is_called = false;
};

/* ------------------------------------------------------------------ */
// for pubind11

static void pybind_adder(py::module &m)
{
  py::class_<Adder,PyUpdater<Adder>,Updater,std::shared_ptr<Adder>>(m, "Adder")
    .def(py::init<>());
}

#endif