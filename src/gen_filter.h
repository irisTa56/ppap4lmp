/* ---------------------------------------------------------------------
GenFilter: stands for Generator for Filtered data.

create: 2018/06/28 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_FILTER_H
#define GEN_FILTER_H

#include "generator.h"

class GenFilter : public Generator {
 public:
  GenFilter(std::shared_ptr<Generator>);
  virtual ~GenFilter() = default;
  virtual void appoint() override;
 protected:
  std::shared_ptr<Generator> original;
  /* NOTE:
  You need to say goodbye to the original Generator at the end of
  generate() concritized elsewhere.
  */
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_gen_filter(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<GenFilter,PyGenerator<GenFilter>,Generator,std::shared_ptr<GenFilter>>(m, "GenFilter")
    .def(py::init<std::shared_ptr<Generator>>());
}

#endif