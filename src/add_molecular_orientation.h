/* ---------------------------------------------------------------------
AddMolecularOrientation: stands for Adder for Molecular Orientation.

create: 2018/07/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_MOLECULAR_ORIENTATION_H
#define ADD_MOLECULAR_ORIENTATION_H

#include "adder.h"

class AddMolecularOrientation : public Adder {
 protected:
  virtual void compute_impl(Json &, Set<Str> &) override;
 public:
  using Adder::Adder;
  virtual ~AddMolecularOrientation() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_molecular_orientation(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddMolecularOrientation,PyUpdater<AddMolecularOrientation>,Adder,Updater,ShPtr<AddMolecularOrientation>>(m, "AddMolecularOrientation")
    .def(py::init<>());
}

#endif