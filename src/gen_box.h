/* ---------------------------------------------------------------------
GenBox: stands for Generator of Box.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_BOX_H
#define GEN_BOX_H

#include "generator.h"

class GenBox : public Generator {
 public:
  GenBox();
  GenBox(const std::string &);
  virtual ~GenBox() = default;
  const std::vector<bool> get_periodic();
  const std::vector<std::unordered_map<std::string,double>> get_edge();
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_gen_box(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<GenBox,PyGenerator<GenBox>,Generator,std::shared_ptr<GenBox>>(m, "GenBox")
    .def(py::init<>())
    .def(py::init<const std::string &>())
    .def("get_periodic", &GenBox::get_periodic)
    .def("get_edge", &GenBox::get_edge);
}

#endif