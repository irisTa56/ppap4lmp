/* ---------------------------------------------------------------------
AddMap: stands for Adder Mapping an existing property to a new property.

create: 2018/06/26 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_MAP_H
#define ADD_MAP_H

#include "adder.h"

class AddMap : public Adder {
 public:
  AddMap(const std::string &, const std::string &, pybind11::dict);
 protected:
  virtual void compute_impl(nlohmann::json &) override;
 private:
  std::string key_ref;
  std::string key_new;
  std::unordered_map<nlohmann::json,nlohmann::json> mapping;
  const nlohmann::json convert_py2json(const pybind11::handle &);
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_add_map(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddMap,PyAdder<AddMap>,Adder,std::shared_ptr<AddMap>>(m, "AddMap")
    .def(py::init<const std::string &, const std::string &, pybind11::dict>());
}

#endif