#ifndef PYBIND_PROESSOR_H
#define PYBIND_PROESSOR_H

#include <alias/pybind.h>
#include <processors/processor.h>

// trampoline class to bind Python
template <class PRO = Processor>
class PyProcessor : public PRO {
 protected:
  void run_impl(
    const int index) override
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
