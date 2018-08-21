/* ---------------------------------------------------------------------
AddGyrationRadius: stands for Adder for Gyration Radius (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_GYRATION_RADIUS_H
#define ADD_GYRATION_RADIUS_H

#include "adder.h"

class AddGyrationRadius : public Adder {
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  using Adder::Adder;
  virtual ~AddGyrationRadius() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_gyration_radius(py::module &m)
{
  py::class_<AddGyrationRadius,PyUpdater<AddGyrationRadius>,Adder,Updater,ShPtr<AddGyrationRadius>>(m, "AddGyrationRadius")
    .def(py::init<>());
}

#endif