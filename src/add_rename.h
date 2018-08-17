/* ---------------------------------------------------------------------
AddRename: stands for Adder to create new property by Renaming existing
property.

create: 2018/08/17 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_RENAME_H
#define ADD_RENAME_H

#include "adder.h"

class AddRename : public Adder {
  bool overwrite;
  Str key_old;
  Str key_new;
 protected:
  virtual void compute_impl(Json &, Set<Str> &) override;
 public:
  AddRename(const Str &, const Str &);
  AddRename(const Str &, const Str &, bool);
  virtual ~AddRename() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_rename(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddRename,PyUpdater<AddRename>,Adder,Updater,ShPtr<AddRename>>(m, "AddRename")
    .def(py::init<const Str &,const Str &>())
    .def(py::init<const Str &,const Str &,bool>());
}

#endif