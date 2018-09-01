/* ---------------------------------------------------------------------
Adder: is an abstract class to add new properties to data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADDER_H
#define ADDER_H

#include <updaters/updater.h>

class Adder : public Updater {
 public:
  using Updater::Updater;
  virtual ~Adder() = default;
  virtual void compute(
    Json &data,
    Set<Str> &datakeys,
    int dataid) override;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_adder(py::module &m)
{
  py::class_<
    Adder,PyUpdater<Adder>,Updater,ShPtr<Adder>>(m, "Adder")
    .def(py::init<>());
}

#endif