/*!
  @file src/pybind/processors/py_pro_data.h
  @brief This file is for binding AddRename class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/17
  @details

  <table class="py_table">
    <caption>
      Python-side constructor of AddRename
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %AddRename</td>
      <td class="py_td">AddRename::AddRename</td>
      <td class="py_td">
        Constructor of AddRename class.
      </td>
      <td class="py_td">
        - \c key_old_ : A string key for an existing property to be
          renamed.
        - \c key_new_ : A string key by which the old key
          for the existing property is renamed.
      </td>
      <td class="py_td">
        Constructed AddRename object.
      </td>
    </tr>
  </table>

  <table class="py_table">
    <caption>
      Python-side methods of AddRename
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c overwrite</td>
      <td class="py_td">AddRename::overwrite</td>
      <td class="py_td">
        Allow overwriting an existing property by a renamed property
        (another existing property) with the same name.
      </td>
      <td class="py_td">
        - \c do_overwrite_ : A boolean, whether overwriting is
          allowed or not. No argument leads to allowing overwriting.
      </td>
      <td class="py_td">
        This AddRename object.
      </td>
    </tr>
  </table>
*/

#ifndef PYBIND_PRO_DATA_H
#define PYBIND_PRO_DATA_H

#include <processors/pro_data.h>
#include <pybind/processors/py_processor.h>

//! Function to bind ProData class to Python.
static void pybind_pro_data(py::module &m)
{
  py::class_<ProData,PyProcessor<ProData>,Processor,ShPtr<ProData>>(m, "ProData")
    .def(py::init<const ElPtr &>())
    .def(py::init<const Vec<ElPtr> &>())
    .def("select", &ProData::select)
    .def("get_results", &ProData::get_results);
}

#endif
