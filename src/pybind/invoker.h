#ifndef PYBIND_INVOKER_H
#define PYBIND_INVOKER_H

#include <invokers/invoker.h>

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
