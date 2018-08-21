/* ---------------------------------------------------------------------
Invoker: is an abstract class to execute processes.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef INVOKER_H
#define INVOKER_H

#include "processor.h"

class Invoker {
 protected:
  int n_processors;
  List<ShPtr<Processor>> processors;
  virtual void execute_impl() = 0;
 public:
  Invoker(
    ShPtr<Processor> proc);
  Invoker(
    std::vector<ShPtr<Processor>> procs);
  virtual ~Invoker() = default;
  void execute();
};

/* ------------------------------------------------------------------ */
// for pybind11

// trampoline class to bind Python
template <class INVO = Invoker>
class PyInvoker : public INVO {
 protected:
  void execute_impl() override
  {
    PYBIND11_OVERLOAD_PURE(
      void, INVO, execute_impl, );
  }
 public:
  using INVO::INVO;
};

static void pybind_invoker(py::module &m)
{
  py::class_<
    Invoker,PyInvoker<>,ShPtr<Invoker>>(m, "Invoker")
    .def(py::init<ShPtr<Processor>>())
    .def(py::init<std::vector<ShPtr<Processor>>>())
    .def("execute", &Invoker::execute);
}

#endif
