/* ---------------------------------------------------------------------
AddWrappedPositions: stands for Adder for Wrapped Postisions.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_WRAPPED_POSITIONS_H
#define ADD_WRAPPED_POSITIONS_H

#include "adder.h"

class AddWrappedPositions : public Adder {
 protected:
  virtual void compute_impl(Json &, Set<Str> &) override;
 public:
  AddWrappedPositions(ShPtr<GenElement>);
  virtual ~AddWrappedPositions() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_wrapped_positions(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddWrappedPositions,PyUpdater<AddWrappedPositions>,Adder,Updater,ShPtr<AddWrappedPositions>>(m, "AddWrappedPositions")
    .def(py::init<ShPtr<GenElement>>());
}

#endif