/* ---------------------------------------------------------------------
Invoker: is an abstract class to execute processes.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef INVOKER_H
#define INVOKER_H

#include "processor.h"

class Invoker {
 public:
  Invoker(std::shared_ptr<Processor>);
  Invoker(std::vector<std::shared_ptr<Processor>>);
  virtual ~Invoker() = default;
  virtual void execute();
  int get_n_processors();
 protected:
  int n_processors;
  int n_generators;
  std::vector<std::shared_ptr<Processor>> processors;
  // implementations
  virtual void execute_impl() = 0;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class INVO = Invoker>
class PyInvoker : public INVO {
 public:
  using INVO::INVO;
  void execute() override {
    PYBIND11_OVERLOAD(void, INVO, execute, );
  }
 protected:
  void execute_impl() override {
    PYBIND11_OVERLOAD_PURE(void, INVO, execute_impl, );
  }
};

static void pybind_invoker(py::module &m)  {

  py::class_<Invoker,PyInvoker<>,std::shared_ptr<Invoker>>(m, "Invoker")
    .def(py::init<std::shared_ptr<Processor>>())
    .def(py::init<std::vector<std::shared_ptr<Processor>>>())
    .def("execute", &Invoker::execute);

}

#endif
