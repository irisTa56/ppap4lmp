/* ---------------------------------------------------------------------
ParDumpAtoms: stands for Parser to read lammps' Dump file and extract
Atoms data (supposed to be used by GenAtoms).

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
  virtual void compute(nlohmann::json &) override;
 private:
  const std::vector<bool> get_is_int_vector(const std::string &);
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_par_dump_atoms(py::module &m)
{
  py::class_<ParDumpAtoms,PyParser<ParDumpAtoms>,ParDump,Parser,std::shared_ptr<ParDumpAtoms>>(m, "ParDumpAtoms")
    .def(py::init<const std::string &, int>());
}

#endif