#ifndef PYBIND_PRO_DATA_H
#define PYBIND_PRO_DATA_H

#include <processors/pro_data.h>
#include <pybind/processors_py/processor.h>

static void pybind_pro_data(py::module &m)
{
  py::class_<ProData,PyProcessor<ProData>,Processor,ShPtr<ProData>>(m, "ProData")
    .def(py::init<const ElPtr &>())
    .def(py::init<const Vec<ElPtr> &>())
    .def("select", &ProData::select)
    .def("get_results", &ProData::get_results);
}

#endif
