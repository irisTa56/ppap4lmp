/* ---------------------------------------------------------------------
AddRename: stands for Adder to create new property by Renaming existing
property.

create: 2018/08/17 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_RENAME_H
#define ADD_RENAME_H

#include "adder.h"

class AddRename : public Adder, public EnShThis<AddRename> {
  bool do_overwrite = false;
  Str key_old;
  Str key_new;
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  AddRename(
    const Str &key_old_,
    const Str &key_new_);
  virtual ~AddRename() = default;
  ShPtr<AddRename> overwrite(
    bool do_overwrite_ = true);
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_rename(py::module &m)
{
  py::class_<AddRename,PyUpdater<AddRename>,Adder,Updater,ShPtr<AddRename>>(m, "AddRename")
    .def(py::init<const Str &,const Str &>())
    .def(
      "overwrite", &AddRename::overwrite,
      py::arg("do_overwrite_") = true);
}

#endif