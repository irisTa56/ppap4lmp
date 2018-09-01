/* ---------------------------------------------------------------------
AddWrappedPositions: stands for Adder for Wrapped Postisions.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_WRAPPED_POSITIONS_H
#define ADD_WRAPPED_POSITIONS_H

#include <adders/adder.h>

class AddWrappedPositions : public Adder {
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  AddWrappedPositions(
    ShPtr<GenElement> elem);
  virtual ~AddWrappedPositions() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_wrapped_positions(py::module &m)
{
  py::class_<AddWrappedPositions,PyUpdater<AddWrappedPositions>,Adder,Updater,ShPtr<AddWrappedPositions>>(m, "AddWrappedPositions")
    .def(py::init<ShPtr<GenElement>>());
}

#endif