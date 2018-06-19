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
  virtual void prepare() override;
  virtual void run(int itr) override;
  virtual void dry_run(int itr) override;
  virtual void finish() override {}
  const std::vector<Data *> &get_results();
 protected:
  std::vector<Data *> results;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_proc_data(py::module &m) {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ProcData, PyProcessor<ProcData>, Processor>(m, "ProcData")
    .def(py::init<Extractor *>())
    .def(py::init<std::vector<Extractor *>>())
    .def(
      "get_results", &ProcData::get_results,
      py::return_value_policy::reference_internal);

}

#endif
