/* ---------------------------------------------------------------------
This file is for Processor class.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <memory>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "generator.h"

class Processor {
 public:
  Processor(std::shared_ptr<Generator>);
  Processor(std::vector<std::shared_ptr<Generator>>);
  virtual ~Processor() = default;
  virtual void prepare() = 0;
  virtual void run(int i_generator) = 0;
  virtual void finish() = 0;
  const int get_n_generators();
 protected:
  std::vector<std::shared_ptr<Generator>> generators;
  int n_generators;
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
  void run(int i_generator) override {
    PYBIND11_OVERLOAD_PURE(void, PROC, run, i_generator);
  }
  void finish() override {
    PYBIND11_OVERLOAD_PURE(void, PROC, finish, );
  }
};

static void pybind_processor(py::module &m)  {

  py::class_<Processor, PyProcessor<>>(m, "Processor")
    .def(py::init<std::shared_ptr<Generator>>())
    .def(py::init<std::vector<std::shared_ptr<Generator>>>())
    .def("get_n_generators", &Processor::get_n_generators);

}

#endif
