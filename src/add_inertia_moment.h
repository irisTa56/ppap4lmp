/* ---------------------------------------------------------------------
AddInertiaMoment: stands for Adder for Inertia Moment (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_INERTIA_MOMENT_H
#define ADD_INERTIA_MOMENT_H

#include "adder.h"

class AddInertiaMoment : public Adder {
 protected:
  virtual void compute_impl(json &) override;
 public:
  AddInertiaMoment(std::shared_ptr<Generator>);
  virtual ~AddInertiaMoment() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_inertia_moment(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddInertiaMoment,PyUpdater<AddInertiaMoment>,Adder,Updater,std::shared_ptr<AddInertiaMoment>>(m, "AddInertiaMoment")
    .def(py::init<std::shared_ptr<Generator>>());
}

#endif