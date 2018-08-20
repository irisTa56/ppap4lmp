/* ---------------------------------------------------------------------
AddMap: stands for Adder for Mapping from existing properties to new
properties.

create: 2018/06/26 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_MAP_H
#define ADD_MAP_H

#include "adder.h"

class AddMap : public Adder, public EnableShThis<AddMap> {
  bool do_overwrite = false;
  Str key_ref;
  Str key_new;
  Dict<Json,Json> mapping;
 protected:
  virtual void compute_impl(Json &, Set<Str> &) override;
 public:
  AddMap(const Str &, const Str &, const Dict<Json,Json> &);
  virtual ~AddMap() = default;
  ShPtr<AddMap> overwrite(bool do_overwrite_ = true);
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_map(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddMap,PyUpdater<AddMap>,Adder,Updater,ShPtr<AddMap>>(m, "AddMap")
    .def(py::init<const Str &,const Str &,const Dict<Json,Json> &>())
    .def(
      "overwrite", &AddMap::overwrite,
      py::arg("do_overwrite_") = true);
}

#endif