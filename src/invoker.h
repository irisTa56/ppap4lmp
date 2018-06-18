/* ---------------------------------------------------------------------
This file is for Invoker class.

create: 2018/06/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef INVOKER_H
#define INVOKER_H

#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "processor.h"

class Invoker {
 public:
  Invoker(Processor *);
  Invoker(std::vector<Processor *>);
  virtual ~Invoker() = default;
  virtual void execute() = 0;
 protected:
  std::vector<Processor *> processors;
  int n_iteration;
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
    PYBIND11_OVERLOAD_PURE(void, INVO, execute, );
  }
};

static void pybind_invoker(py::module &m)  {

  py::class_<Invoker, PyInvoker<>>(m, "Invoker")
    .def(py::init<Processor *>())
    .def(py::init<std::vector<Processor *>>())
    .def(
      "execute", &Invoker::execute,
      py::return_value_policy::reference_internal);

}

#endif



/*

Invoker::Invoker() { }
Invoker::~Invoker() {
    std::list<Command*>::iterator it = commandQueue_.begin();
    while (it != commandQueue_.end()) {
        delete (*it);
        ++it;
    }
}
void Invoker::Store(Command* cmd) {
    commandQueue_.push_back(cmd);
}
void Invoker::Execute() {
    while (!commandQueue_.empty()) {
        Command* command = commandQueue_.front();
        commandQueue_.pop_front();
        command->Execute();
        delete command;
    }
}
*/