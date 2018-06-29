/* ---------------------------------------------------------------------
ParDumpBox: stands for Parser to read lammps' Dump file and extract
Box data (supposed to be used by GenBox).

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PAR_DUMP_BOX_H
#define PAR_DUMP_BOX_H

#include "par_dump.h"

class ParDumpBox : public ParDump {
 public:
  using ParDump::ParDump;
  virtual ~ParDumpBox() = default;
 protected:
  virtual void compute(nlohmann::json &) override;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_par_dump_box(py::module &m)
{
  py::class_<ParDumpBox,PyParser<ParDumpBox>,ParDump,Parser,std::shared_ptr<ParDumpBox>>(m, "ParDumpBox")
    .def(py::init<const std::string &, int>());
}

#endif