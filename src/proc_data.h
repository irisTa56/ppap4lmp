/* ---------------------------------------------------------------------
This file is for ProcData class.

create: 2018/06/18 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PROC_DATA_H
#define PROC_DATA_H

#include "processor.h"

class ProcData : public Processor {
 public:
  ProcData(Extractor *extr) : Processor(extr) {}
  ProcData(std::vector<Extractor *> extrs) : Processor(extrs) {}
  virtual ~ProcData() = default;
  virtual void prepare() = 0;
  virtual void run() = 0;
  virtual void dry_run() = 0;
 protected:
  virtual void process() = 0;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_proc_data(py::module &m) {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ProcData, PyProcessor<ProcData>>(m, "ProcData")
    .def(py::init<Extractor *>())
    .def(py::init<std::vector<Extractor *>>());

}

#endif
