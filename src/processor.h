/* ---------------------------------------------------------------------
This file is for Processor class.

create: 2018/06/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <pybind11/pybind11.h>

class Processor {
 public:
  Processor() = default;
  virtual ~Processor() = default;
  virtual void prepare() = 0;
  virtual void prepare(int) = 0;
  virtual void run() = 0;
  virtual void run(int) = 0;
  virtual void dry_run() = 0;
  virtual void dry_run(int) = 0;
 protected:
  virtual void process() = 0;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_processor(py::module &m)  {}

#endif
