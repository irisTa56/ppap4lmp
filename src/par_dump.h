/* ---------------------------------------------------------------------
ParDump: stands for Parser reading lammps' Dump file.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PAR_DUMP_H
#define PAR_DUMP_H

#include "parser.h"

class ParDump : public Parser {
 public:
  ParDump(const std::string &, int);
  virtual ~ParDump() = default;
 protected:
  int timestep;
  std::string filepath;
};

/* ------------------------------------------------------------------ */
// for pubind11

static void pybind_par_dump(py::module &m)
{
  py::class_<ParDump,PyUpdater<ParDump>,Parser,Updater,std::shared_ptr<ParDump>>(m, "ParDump")
    .def(py::init<const std::string &, int>());
}

#endif