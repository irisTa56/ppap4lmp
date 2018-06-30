/* ---------------------------------------------------------------------
ParDumpAtoms: stands for Parser reading lammps' Dump file and
extracting Atoms data (supposed to be used by GenAtoms).

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PAR_DUMP_ATOMS_H
#define PAR_DUMP_ATOMS_H

#include "par_dump.h"

class ParDumpAtoms : public ParDump {
 public:
  using ParDump::ParDump;
  virtual ~ParDumpAtoms() = default;
 protected:
  virtual void compute_impl(nlohmann::json &) override;
 private:
  const std::vector<bool> get_is_int_vector(const std::string &);
};

/* ------------------------------------------------------------------ */
// for pubind11

static void pybind_par_dump_atoms(py::module &m)
{
  py::class_<ParDumpAtoms,PyUpdater<ParDumpAtoms>,ParDump,Parser,Updater,std::shared_ptr<ParDumpAtoms>>(m, "ParDumpAtoms")
    .def(py::init<const std::string &, int>());
}

#endif