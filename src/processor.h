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
  virtual void run(int itr) = 0;
  virtual void dry_run(int itr) = 0;
  virtual void finish() = 0;
  int get_length();
 protected:
  std::vector<Extractor *> extractors;
  int length;
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
  void run(int itr) override {
    PYBIND11_OVERLOAD_PURE(void, PROC, run, itr);
  }
  void dry_run(int itr) override {
    PYBIND11_OVERLOAD_PURE(void, PROC, dry_run, itr);
  }
  void finish() override {
    PYBIND11_OVERLOAD_PURE(void, PROC, finish, );
  }
};

static void pybind_processor(py::module &m)  {

  py::class_<Processor, PyProcessor<>>(m, "Processor")
    .def(py::init<Extractor *>())
    .def(py::init<std::vector<Extractor *>>())
    .def(
      "get_length", &Processor::get_length,
      py::return_value_policy::reference_internal);

}

#endif
