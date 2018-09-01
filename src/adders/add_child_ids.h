/* ---------------------------------------------------------------------
AddChildIDs: stands for Adder for Child IDs (such as atom-ids in the
case of molecules).

create: 2018/08/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_CHILD_IDS_H
#define ADD_CHILD_IDS_H

#include <adders/adder.h>

class AddChildIDs : public Adder {
  Str child_name;
  Str key_for_parent_id;
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  AddChildIDs(
    ShPtr<GenElement> elem,
    const Str &child_name_,
    const Str &key_for_parent_id_);
  virtual ~AddChildIDs() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_child_ids(py::module &m)
{
  py::class_<AddChildIDs,PyUpdater<AddChildIDs>,Adder,Updater,ShPtr<AddChildIDs>>(m, "AddChildIDs")
    .def(py::init<ShPtr<GenElement>,const Str &,const Str &>());
}

#endif