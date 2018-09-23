/*!
  @file src/pybind/processors/py_processor.cpp
  @brief This file is for binding Processor class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_processor.h"

void pybind::py_processor(py::module &m)
{
  py::class_<
    Processor,PyProcessor<>,ShPtr<Processor>>(m, "Processor")
    .def(py::init<>());
}
