#ifndef PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H
#define PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H

#include <processors/pro_radial_distribution_function_with_deformation.h>
#include <pybind/processors/processor.h>

static void pybind_pro_radial_distribution_function_with_deformation(py::module &m)
{
  py::class_<ProRDFWD,PyProcessor<ProRDFWD>,Processor,ShPtr<ProRDFWD>>(m, "ProRDFWD")
    .def(py::init<const ElPtr &,const ElPtr &>())
    .def(py::init<const Vec<std::pair<ElPtr,ElPtr>> &>())
    .def("set_margin", &ProRDFWD::set_margin);
}

#endif
