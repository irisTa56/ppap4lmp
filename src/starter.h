/* ---------------------------------------------------------------------
Starter: is an abstract class to parse data from a file or other data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STARTER_H
#define STARTER_H

#include "updater.h"

class Starter : public Updater {
 public:
  using Updater::Updater;
  virtual ~Starter() = default;
  virtual void compute(Json &, Set<Str> &, int) override;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_starter(py::module &m)
{
  py::class_<
    Starter,PyUpdater<Starter>,Updater,ShPtr<Starter>>(m, "Starter")
    .def(py::init<>());
}

#endif