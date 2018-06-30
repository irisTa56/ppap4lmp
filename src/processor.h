/* ---------------------------------------------------------------------
Processor: is an abstract class to process data.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PROESSOR_H
#define PROESSOR_H

#include "generator.h"

class Processor {
 public:
  Processor(std::shared_ptr<Generator>);
  Processor(std::vector<std::shared_ptr<Generator>>);
  virtual ~Processor() = default;
  virtual void run(int i_generator);
  void prepare();
  void finish();
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

// trampoline class to bind Python
template <class PRO = Processor>
class PyProcessor : public PRO {
 public:
  using PRO::PRO;
  void run(int i_generator) override
  {
    PYBIND11_OVERLOAD(void, PRO, run, i_generator);
  }
 protected:
  void run_impl(int i_generator) override
  {
    PYBIND11_OVERLOAD_PURE(void, PRO, run_impl, i_generator);
  }
  void prepare_impl() override
  {
    PYBIND11_OVERLOAD(void, PRO, prepare_impl, );
  }
  void finish_impl() override
  {
    PYBIND11_OVERLOAD(void, PRO, finish_impl, );
  }
};

static void pybind_processor(py::module &m)
{
  py::class_<Processor,PyProcessor<>,std::shared_ptr<Processor>>(m, "Processor")
    .def(py::init<std::shared_ptr<Generator>>())
    .def(py::init<std::vector<std::shared_ptr<Generator>>>());
}

#endif
