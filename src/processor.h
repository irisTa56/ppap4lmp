/* ---------------------------------------------------------------------
This file is for Processor class.

create: 2018/06/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "extractor.h"

class Processor {
 public:
  Processor(Extractor *);
  Processor(std::vector<Extractor *>);
  virtual ~Processor() = default;
  virtual void prepare() = 0;
  virtual void run() = 0;
  virtual void dry_run() = 0;
 protected:
  virtual void process() = 0;
  std::vector<Extractor *> extractors;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class PROC = Processor>
class PyProcessor : public PROC {
 public:
  using PROC::PROC;
  void prepare() override {
    PYBIND11_OVERLOAD_PURE(void, PROC, prepare, );
  }
  void run() override {
    PYBIND11_OVERLOAD_PURE(void, PROC, run, );
  }
  void dry_run() override {
    PYBIND11_OVERLOAD_PURE(void, PROC, dry_run, );
  }
 protected:
  void process() override {
    PYBIND11_OVERLOAD_PURE(void, PROC, process, );
  }
};

static void pybind_processor(py::module &m)  {

  py::class_<Processor, PyProcessor<>>(m, "Processor")
    .def(py::init<Extractor *>())
    .def(py::init<std::vector<Extractor *>>());

}

#endif
