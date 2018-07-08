/* ---------------------------------------------------------------------
AddWrappedPositions: stands for Adder for Wrapped Postisions ('x', 'y',
'z').

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_WRAPPED_POSITIONS_H
#define ADD_WRAPPED_POSITIONS_H

#include "adder.h"

class AddWrappedPositions : public Adder {
 protected:
  virtual void compute_impl(nlohmann::json &) override;
 public:
  AddWrappedPositions(std::shared_ptr<Generator>);
  virtual ~AddWrappedPositions() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_wrapped_positions(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddWrappedPositions,PyUpdater<AddWrappedPositions>,Adder,Updater,std::shared_ptr<AddWrappedPositions>>(m, "AddWrappedPositions")
    .def(py::init<std::shared_ptr<Generator>>());
}

#endif