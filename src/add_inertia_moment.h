/* ---------------------------------------------------------------------
AddInertiaMoment: stands for Adder for Inertia Moment (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_INERTIA_MOMENT_H
#define ADD_INERTIA_MOMENT_H

#include "adder.h"

class AddInertiaMoment : public Adder {
  void compute_with_weights(Json &data, ShPtr<GenElement>);
  void compute_without_weights(Json &data, ShPtr<GenElement>);
 protected:
  virtual void compute_impl(Json &, Set<Str> &) override;
 public:
  AddInertiaMoment(ShPtr<GenElement>);
  virtual ~AddInertiaMoment() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_inertia_moment(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddInertiaMoment,PyUpdater<AddInertiaMoment>,Adder,Updater,ShPtr<AddInertiaMoment>>(m, "AddInertiaMoment")
    .def(py::init<ShPtr<GenElement>>());
}

#endif