/* ---------------------------------------------------------------------
AddMap: stands for Adder Mapping an existing property to a new property.

create: 2018/06/26 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_MAP_H
#define ADD_MAP_H

#include "adder.h"

class AddMap : public Adder {
  std::string key_ref;
  std::string key_new;
  std::unordered_map<json,json> mapping;
 protected:
  virtual void compute_impl(json &) override;
 public:
  AddMap(
    const std::string &, const std::string &,
    const std::unordered_map<json,json> &);
  virtual ~AddMap() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_map(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddMap,PyUpdater<AddMap>,Adder,Updater,std::shared_ptr<AddMap>>(m, "AddMap")
    .def(
      py::init<const std::string &,const std::string &,const std::unordered_map<json,json> &>());
}

#endif