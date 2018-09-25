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

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of InvOMP.
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          InvOMP::Invoker
        </td>
        <td class="py_constructor" colspan="2">
          Constructor of InvOMP class,
          which uses one Processor object.
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails InvOMP::Invoker(const ShPtr<Processor> &)
        </td>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          InvOMP::Invoker
        </td>
        <td class="py_constructor" colspan="2">
          Constructor of InvOMP class,
          which uses multiple Processor objects.
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails InvOMP::Invoker(const Vec<ShPtr<Processor>> &)
        </td>
      </tr>
    </table>

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of InvOMP
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c execute</td>
        <td class="py_method">InvOMP::execute</td>
        <td class="py_method">
          @copybrief InvOMP::execute
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
    </table>
  */
  void py_inv_omp(py::module &m);
}

#endif
