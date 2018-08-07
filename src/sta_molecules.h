/* ---------------------------------------------------------------------
StaMolecules: stands for Starter to generate Molecules from Atoms.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_MOLECULES_H
#define STA_MOLECULES_H

#include "starter.h"

class StaMolecules : public Starter {
 protected:
  virtual void compute_impl(json &) override;
 public:
  StaMolecules(std::shared_ptr<Generator>);
  virtual ~StaMolecules() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_sta_molecules(py::module &m)
{
  py::class_<StaMolecules,PyUpdater<StaMolecules>,Starter,Updater,std::shared_ptr<StaMolecules>>(m, "StaMolecules")
    .def(py::init<std::shared_ptr<Generator>>());
}

#endif