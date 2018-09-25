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

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind Invoker class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    Constructor of Invoker class is hidden from Python,
    because the class is an abstract one.
  */
  void py_invoker(py::module &m);
}

#endif
