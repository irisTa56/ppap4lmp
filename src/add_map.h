/* ---------------------------------------------------------------------
AddMap: stands for Adder Mapping an existing property to a new property.

create: 2018/06/26 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_MAP_H
#define ADD_MAP_H

#include "adder.h"

using JsonJson = std::unordered_map<nlohmann::json,nlohmann::json>;

class AddMap : public Adder {
 public:
  AddMap(const std::string &, const std::string &, JsonJson);
 protected:
  virtual void compute_impl(nlohmann::json &) override;
 private:
  std::string key_ref;
  std::string key_new;
  JsonJson mapping;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_map(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddMap,PyUpdater<AddMap>,Adder,Updater,std::shared_ptr<AddMap>>(m, "AddMap")
    .def(py::init<const std::string &,const std::string &,JsonJson>());
}

#endif