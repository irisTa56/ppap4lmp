/*!
  @file src/pybind/processors/py_processor.h
  @brief This file is for binding Processor class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/22
*/

#ifndef PYBIND_PROESSOR_H
#define PYBIND_PROESSOR_H

#include <alias/pybind.h>
#include <processors/processor.h>

/*!
  @brief Trampoline class to bind Processor class and its subclasses
  to Python.
  @details For more details, please see pybind11 documentation:
  https://pybind11.readthedocs.io/en/stable/advanced/classes.html.
*/
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

/*!
  @brief Function to bind Processor class to Python.
  @details Constructor of Processor class is hidden from Python,
  because the class is an abstract one.
*/
static void pybind_processor(py::module &m)
{
  py::class_<
    Processor,PyProcessor<>,ShPtr<Processor>>(m, "Processor")
    .def(py::init<>());
}

#endif
