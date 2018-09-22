/*!
  @file src/pybind/processors/py_pro_data.h
  @brief This file is for binding ProData class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/22
  @details

  <table class="py_table">
    <caption>
      Python-side constructor of ProData
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %ProData</td>
      <td class="py_td">ProData::ProData</td>
      <td class="py_td">
        Constructor of ProData class for one Element object.
      </td>
      <td class="py_td">
        - \c elem : An Element object to be copied.
      </td>
      <td class="py_td">
        Constructed ProData object.
      </td>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %ProData</td>
      <td class="py_td">ProData::ProData</td>
      <td class="py_td">
        Constructor of ProData class for a trajectory
        of Element objects.
      </td>
      <td class="py_td">
        - \c elems : List of Element objects to be copied.
      </td>
      <td class="py_td">
        Constructed ProData object.
      </td>
    </tr>
  </table>

  <table class="py_table">
    <caption>
      Python-side methods of ProData
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c select</td>
      <td class="py_td">ProData::select</td>
      <td class="py_td">
        Specify string keys for properties to be copied.
      </td>
      <td class="py_td">
        - \c do_overwrite_ : A boolean, whether overwriting is
          allowed or not. No argument leads to allowing overwriting.
      </td>
      <td class="py_td">
        This ProData object.
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
