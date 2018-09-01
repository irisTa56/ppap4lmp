/* ---------------------------------------------------------------------
InvOMP: stands for Invoker using OpenMP.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef INV_OMP_H
#define INV_OMP_H

#include <invokers/invoker.h>

class InvOMP : public Invoker {
 protected:
  virtual void execute_impl() override;
 public:
  using Invoker::Invoker;
  virtual ~InvOMP() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_inv_omp(py::module &m)
{
  py::class_<InvOMP,PyInvoker<InvOMP>,Invoker,ShPtr<InvOMP>>(m, "InvOMP")
    .def(py::init<ShPtr<Processor>>())
    .def(py::init<List<ShPtr<Processor>>>());
}

#endif
