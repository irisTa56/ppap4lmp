/*!
  @file src/pybind/py_updater.h
  @brief This file is for binding Updater class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef PYBIND_UPDATER_H
#define PYBIND_UPDATER_H

#include <alias/pybind.h>
#include <core/updater.h>

/*!
  @brief Trampoline class to bind Updater class and its subclasses
  to Python.

  For more details, please see pybind11 documentation:
  https://pybind11.readthedocs.io/en/stable/advanced/classes.html.
*/
template <class UPD = Updater>
class PyUpdater : public UPD {
 protected:
  void compute_impl(
    Json &data,
    DataKeys &datakeys) override
  {
    PYBIND11_OVERLOAD_PURE(
      void, UPD, compute_impl, data, datakeys);
  }
 public:
  using UPD::UPD;
  void compute(
    Json &data,
    DataKeys &datakeys,
    const int dataid) override
  {
    PYBIND11_OVERLOAD_PURE(
      void, UPD, compute, data, datakeys, dataid);
  }
};

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind Updater class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    Constructor of Updater class is hidden from Python,
    because the class is an abstract one.
  */
  void py_updater(py::module &m);
}

#endif