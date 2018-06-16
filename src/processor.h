/* ---------------------------------------------------------------------
This file is for Processor class.

create: 2018/06/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

#include "data.h"

namespace py = pybind11;

class Processor {
 public:
  Processor();
  void execute(const Data &);
  const std::string &get_result() const;
 private:
  std::string dataname;
};

/* ------------------------------------------------------------------ */
// for pubind11

static void setup_pybind_processor(py::module &m)  {

  py::class_<Processor>(m, "Processor")
    .def(py::init<>())
    .def("execute", &Processor::execute)
    .def("get_result", &Processor::get_result);

}

#endif
