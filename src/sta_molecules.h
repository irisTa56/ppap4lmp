/* ---------------------------------------------------------------------
StaMolecules: stands for Starter to generate Molecules from atoms.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_MOLECULES_H
#define STA_MOLECULES_H

#include "starter.h"

class StaMolecules : public Starter {
 protected:
  virtual void compute_impl(Json &, Set<Str> &) override;
 public:
  StaMolecules(ShPtr<GenElement>);
  virtual ~StaMolecules() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_sta_molecules(py::module &m)
{
  py::class_<StaMolecules,PyUpdater<StaMolecules>,Starter,Updater,ShPtr<StaMolecules>>(m, "StaMolecules")
    .def(py::init<ShPtr<GenElement>>());
}

#endif