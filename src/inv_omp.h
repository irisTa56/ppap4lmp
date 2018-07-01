/* ---------------------------------------------------------------------
InvOMP: stands for Invoker using OpenMP.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef INV_OMP_H
#define INV_OMP_H

#include "invoker.h"

class InvOMP : public Invoker {
 public:
  using Invoker::Invoker;
  virtual ~InvOMP() = default;
 protected:
  virtual void execute_impl() override;
};

/* ------------------------------------------------------------------ */
// for pubind11

static void pybind_inv_omp(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<InvOMP,PyInvoker<InvOMP>,Invoker,std::shared_ptr<InvOMP>>(m, "InvOMP")
    .def(py::init<std::shared_ptr<Processor>>())
    .def(py::init<std::vector<std::shared_ptr<Processor>>>());
}

#endif
