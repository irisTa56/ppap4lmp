/* ---------------------------------------------------------------------
Processor: is an abstract class to process data.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "generator.h"

class Processor {
 public:
  Processor(std::shared_ptr<Generator>);
  Processor(std::vector<std::shared_ptr<Generator>>);
  virtual ~Processor() = default;
  virtual void run(int i_generator);
  virtual void prepare();
  virtual void finish();
  const int get_n_generators();
 protected:
  int n_generators;
  std::vector<std::shared_ptr<Generator>> generators;
  // implementations
  virtual void run_impl(int i_generator) = 0;
  virtual void prepare_impl() {}
  virtual void finish_impl() {}
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class PROC = Processor>
class PyProcessor : public PROC {
 public:
  using PROC::PROC;
  void run(int i_generator) override {
    PYBIND11_OVERLOAD(void, PROC, run, i_generator);
  }
  void prepare() override {
    PYBIND11_OVERLOAD(void, PROC, prepare, );
  }
  void finish() override {
    PYBIND11_OVERLOAD(void, PROC, finish, );
  }
 protected:
  void run_impl(int i_generator) override {
    PYBIND11_OVERLOAD_PURE(void, PROC, run_impl, i_generator);
  }
  void prepare_impl() override {
    PYBIND11_OVERLOAD(void, PROC, prepare_impl, );
  }
  void finish_impl() override {
    PYBIND11_OVERLOAD(void, PROC, finish_impl, );
  }
};

static void pybind_processor(py::module &m)  {

  py::class_<Processor,PyProcessor<>,std::shared_ptr<Processor>>(m, "Processor")
    .def(py::init<std::shared_ptr<Generator>>())
    .def(py::init<std::vector<std::shared_ptr<Generator>>>());

}

#endif
