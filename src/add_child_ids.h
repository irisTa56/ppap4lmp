/* ---------------------------------------------------------------------
AddChildIDs: stands for Adder for Child IDs (such as atom-ids in the
case of molecules).

create: 2018/08/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_CHILD_IDS_H
#define ADD_CHILD_IDS_H

#include "adder.h"

class AddChildIDs : public Adder {
  Str child_name;
  Str key_for_parent_id;
 protected:
  virtual void compute_impl(Json &, Set<Str> &) override;
 public:
  AddChildIDs(ShPtr<GenElement>, const Str &, const Str &);
  virtual ~AddChildIDs() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_child_ids(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddChildIDs,PyUpdater<AddChildIDs>,Adder,Updater,ShPtr<AddChildIDs>>(m, "AddChildIDs")
    .def(py::init<ShPtr<GenElement>,const Str &,const Str &>());
}

#endif