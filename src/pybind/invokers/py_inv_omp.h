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
    @details
    <table class="py_table">
      <caption>
        Python-side constructor of InvOMP
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %InvOMP</td>
        <td class="py_td">InvOMP::Invoker</td>
        <td class="py_td">
          Constructor of InvOMP class for one Processor object.
        </td>
        <td class="py_td">
          - \c proc : A Processor object to be executed
            by the constructed object.
        </td>
        <td class="py_td">
          Constructed InvOMP object.
        </td>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %InvOMP</td>
        <td class="py_td">InvOMP::Invoker</td>
        <td class="py_td">
          Constructor of InvOMP class for multiple Processor objects.
        </td>
        <td class="py_td">
          - \c procs : List of Processor objects to be executed
            by the constructed object.
        </td>
        <td class="py_td">
          Constructed InvOMP object.
        </td>
      </tr>
    </table>

    <table class="py_table">
      <caption>
        Python-side methods of InvOMP
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c execute</td>
        <td class="py_td">InvOMP::execute</td>
        <td class="py_td">
          Execute analysis programmed in the Processor object(s)
          owned by this object.
        </td>
        <td class="py_td">
          None.
        </td>
        <td class="py_td">
          None.
        </td>
      </tr>
    </table>
  */
  void py_inv_omp(py::module &m);
}

#endif
