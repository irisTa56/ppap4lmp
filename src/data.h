/* ---------------------------------------------------------------------
This file is for Data class.

create: 2018/06/12 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef DATA_H
#define DATA_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

namespace py = pybind11;

class Data {
 public:
  Data(const std::string &);
  void set_name(const std::string &);
  const std::string &get_name() const;
 private:
  std::string name;
};

/* ------------------------------------------------------------------ */
// for pubind11

static void setup_pybind_data(py::module &m)  {

  py::module m_sub = m.def_submodule("data");

  py::class_<Data>(m_sub, "Data")
    .def(py::init<const std::string &>())
    .def("set_name", &Data::set_name)
    .def("get_name", &Data::get_name);

}

#endif
