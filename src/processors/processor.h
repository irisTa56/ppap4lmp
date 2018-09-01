/* ---------------------------------------------------------------------
Processor: is an abstract class to process data.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PROESSOR_H
#define PROESSOR_H

#include <generators/generator.h>
#include <key_checker.h>

class Processor : public KeyChecker {
  int i_generator = 0;
 protected:
  int n_generators;
  List<ShPtr<Generator>> generators;
  virtual void run_impl(int) = 0;
  template <class GEN>
  void register_generator(
    ShPtr<GEN> gen);
  template <class GEN>
  void register_generators(
    const List<ShPtr<GEN>> &gens);
 public:
  Processor() = default;
  virtual ~Processor() = default;
  virtual void prepare() {}
  virtual void finish() {}
  virtual bool run();
};

/* ------------------------------------------------------------------ */
// for pybind11

// trampoline class to bind Python
template <class PRO = Processor>
class PyProcessor : public PRO {
 protected:
  void run_impl(
    int index) override
  {
    PYBIND11_OVERLOAD_PURE(
      void, PRO, run_impl, index);
  }
 public:
  using PRO::PRO;
  void prepare() override
  {
    PYBIND11_OVERLOAD(
      void, PRO, prepare, );
  }
  void finish() override
  {
    PYBIND11_OVERLOAD(
      void, PRO, finish, );
  }
  bool run() override
  {
    PYBIND11_OVERLOAD(
      bool, PRO, run, );
  }
};

static void pybind_processor(py::module &m)
{
  py::class_<
    Processor,PyProcessor<>,ShPtr<Processor>>(m, "Processor")
    .def(py::init<>());
}

#endif
