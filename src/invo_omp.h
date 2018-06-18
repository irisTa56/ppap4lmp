/* ---------------------------------------------------------------------
This file is for InvoOMP class.

create: 2018/06/18 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef INVO_OMP_H
#define INVO_OMP_H

#include "invoker.h"

class InvoOMP : public Invoker {
 public:
  InvoOMP(Processor *proc) : Invoker(proc) {}
  InvoOMP(std::vector<Processor *> procs) : Invoker(procs) {}
  virtual ~InvoOMP() = default;
  virtual void execute() override;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_invo_omp(py::module &m)  {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<InvoOMP, PyInvoker<InvoOMP>, Invoker>(m, "InvoOMP")
    .def(py::init<Processor *>())
    .def(py::init<std::vector<Processor *>>());

}

#endif
