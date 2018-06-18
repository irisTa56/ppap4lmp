/* ---------------------------------------------------------------------
This file is for Extractor class.

create: 2018/06/12 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <string>

#include <pybind11/pybind11.h>

#include "data.h"

template <typename DATA>
class Extractor {
 public:
  Extractor() = default;
  virtual ~Extractor() = default;
  void reserve();
  bool del_data();
  const DATA &get_data();
  const DATA &get_data_no_reservation();
 protected:
  virtual void extract() = 0;
  bool is_extracted = false;
  int reservation_count = 0;
  DATA *data;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_extractor(py::module &m) {}

#endif
