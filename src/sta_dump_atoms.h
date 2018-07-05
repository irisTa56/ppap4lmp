/* ---------------------------------------------------------------------
StaDumpAtoms: stands for Starter reading lammps' Dump file and
extracting Atoms data (supposed to be used by GenAtoms).

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_DUMP_ATOMS_H
#define STA_DUMP_ATOMS_H

#include "sta_dump.h"

class StaDumpAtoms : public StaDump {
  const std::vector<bool> get_is_int_vector(const std::string &);
 protected:
  virtual void compute_impl(nlohmann::json &) override;
 public:
  StaDumpAtoms(const std::string &, int);
  virtual ~StaDumpAtoms() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_sta_dump_atoms(py::module &m)
{
  py::class_<StaDumpAtoms,PyUpdater<StaDumpAtoms>,StaDump,Starter,Updater,std::shared_ptr<StaDumpAtoms>>(m, "StaDumpAtoms")
    .def(py::init<const std::string &, int>());
}

#endif