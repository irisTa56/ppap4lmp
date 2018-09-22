/*!
  @file src/pybind/invokers/py_invoker.h
  @brief This file is for binding Invoker class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/23
*/

#ifndef PYBIND_INVOKER_H
#define PYBIND_INVOKER_H

#include <alias/pybind.h>
#include <invokers/invoker.h>

/*!
  @brief Trampoline class to bind Invoker class and its subclasses
  to Python.
  @details For more details, please see pybind11 documentation:
  https://pybind11.readthedocs.io/en/stable/advanced/classes.html.
*/
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

/*!
  @brief Function to bind Invoker class to Python.
  @details Constructor of Invoker class is hidden from Python,
  because the class is an abstract one.
*/
static void pybind_invoker(py::module &m)
{
  py::class_<
    Invoker,PyInvoker<>,ShPtr<Invoker>>(m, "Invoker")
    .def(py::init<const ShPtr<Processor> &>())
    .def(py::init<const Vec<ShPtr<Processor>> &>())
    .def("execute", &Invoker::execute);
}

#endif
