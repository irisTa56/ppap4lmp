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
  virtual void finish() {}
  virtual bool run();
  void prepare();
 protected:
  int n_generators;
  std::vector<std::shared_ptr<Generator>> generators;
  virtual void prepare_impl() {}
  virtual void run_impl(int) = 0;
 private:
  int i_generator = 0;
};

/* ------------------------------------------------------------------ */
// for pybind11

// trampoline class to bind Python
template <class PRO = Processor>
class PyProcessor : public PRO {
 public:
  using PRO::PRO;
  void finish() override
  {
    PYBIND11_OVERLOAD(void, PRO, finish, );
  }
  bool run() override
  {
    PYBIND11_OVERLOAD(bool, PRO, run, );
  }
 protected:
  void prepare_impl() override
  {
    PYBIND11_OVERLOAD(void, PRO, prepare_impl, );
  }
  void run_impl(int index) override
  {
    PYBIND11_OVERLOAD_PURE(void, PRO, run_impl, index);
  }
};

static void pybind_processor(py::module &m)
{
  py::class_<Processor,PyProcessor<>,std::shared_ptr<Processor>>(m, "Processor")
    .def(py::init<std::shared_ptr<Generator>>())
    .def(py::init<std::vector<std::shared_ptr<Generator>>>());
}

#endif
