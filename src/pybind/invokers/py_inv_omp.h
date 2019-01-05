/*!
  @file src/pybind/invokers/py_inv_omp.h
  @brief This file is for binding InvOMP class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/23
*/

#ifndef PYBIND_INV_OMP_H
#define PYBIND_INV_OMP_H

#include <invokers/inv_omp.h>
#include <pybind/invokers/py_invoker.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind InvOMP class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    Constructor of InvOMP class is hidden from Python.
    A Python-side function \b execute_omp provides functionality
    to create an InvOMP object and execute analysis using it.

    <table class="py_method">
      <caption class="py_method">
        Python-side functions
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">`execute_omp`</td>
        <td class="py_method">pybind::execute_omp</td>
        <td class="py_method">
          @copybrief pybind::execute_omp(const ShPtr<Processor> &)
        </td>
        <td class="py_method">
          @copydetails pybind::execute_omp(const ShPtr<Processor> &)
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
        <tr class="py_method">
        <td class="py_method">`execute_omp`</td>
        <td class="py_method">pybind::execute_omp</td>
        <td class="py_method">
          @copybrief pybind::execute_omp(const Vec<ShPtr<Processor>> &)
        </td>
        <td class="py_method">
          @copydetails pybind::execute_omp(const Vec<ShPtr<Processor>> &)
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
    </table>
  */
  void py_inv_omp(py::module &m);
  /*!
    @brief Create and use an InvOMP object to conduct analysis
    programmed in a Processor's subclass object.
    @param proc
      A Processor object to be executed.
    @return None.
  */
  void execute_omp(const ShPtr<Processor> &proc);
  /*!
    @brief Create and use an InvOMP object to conduct analysis
    programmed in Processor's subclass objects.
    @param procs
      List of Processor objects to be executed.
    @return None.
  */
  void execute_omp(const Vec<ShPtr<Processor>> &procs);
}

#endif
