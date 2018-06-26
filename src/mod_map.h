/* ---------------------------------------------------------------------
ModMap: stands for Modifier adding new properties by Mapping an
existing properties.

create: 2018/06/24 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef MOD_MAP_H
#define MOD_MAP_H

#include "modifier.h"

class ModMap : public Modifier {
 public:
  ModMap(const std::string &, const std::string &, pybind11::dict);
  virtual void modify(nlohmann::json &) override;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_mod_map(py::module &m) {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ModMap,PyModifier<ModMap>,Modifier,std::shared_ptr<ModMap>>(m, "ModMap")
    .def(py::init<const std::string &, const std::string &, pybind11::dict>());

}

#endif