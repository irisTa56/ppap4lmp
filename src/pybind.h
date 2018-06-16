#ifndef PYBIND_H
#define PYBIND_H

#include "headers_data.h"
#include "headers_processor.h"

PYBIND11_MODULE(_ppap4lmp, m) {
  m.doc() = "PostProcess and Analysis Program for LAMMPS";
#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif

  setup_pybind_data(m);
  setup_pybind_processor(m);

}

#endif
