#ifndef PYBIND_H
#define PYBIND_H

#include "headers_data.h"
#include "headers_extractor.h"
#include "headers_processor.h"

PYBIND11_MODULE(_ppap4lmp, m) {

  pybind_data(m);
  pybind_data_box(m);
  pybind_extractor(m);
  pybind_extr_box(m);
  pybind_extr_box_dump(m);
  pybind_processor(m);
  pybind_proc_data(m);

}

#endif
