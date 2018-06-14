/* ---------------------------------------------------------------------
This file is for Data class.

create: 2018/06/12 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

//#include "main.h"

class Data {
 public:
  Data(const std::string &);
  void set_name(const std::string &);
  const std::string &get_name();
 private:
  std::string name;
};

/* ---------------------------------------------------------------------
  Section for pybind11
--------------------------------------------------------------------- */

namespace py = pybind11;

PYBIND11_MODULE(data, m) {
  m.attr("__name__") = "ppap4lmp.data";
  py::class_<Data>(m, "Data")
    .def(py::init<const std::string &>())
    .def("set_name", &Data::set_name)
    .def("get_name", &Data::get_name);
}
