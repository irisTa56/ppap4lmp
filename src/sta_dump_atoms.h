/* ---------------------------------------------------------------------
StaDumpAtoms: stands for Starter reading lammps' Dump file and
extracting Atoms data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_DUMP_ATOMS_H
#define STA_DUMP_ATOMS_H

#include "sta_dump.h"

class StaDumpAtoms : public StaDump {
  const List<bool> get_is_int_vector(
    const Str &line);
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  using StaDump::StaDump;
  virtual ~StaDumpAtoms() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_sta_dump_atoms(py::module &m)
{
  py::class_<StaDumpAtoms,PyUpdater<StaDumpAtoms>,StaDump,Starter,Updater,ShPtr<StaDumpAtoms>>(m, "StaDumpAtoms")
    .def(py::init<const Str &, int>());
}

#endif