/* ---------------------------------------------------------------------
StaDumpBox: stands for Starter reading lammps' Dump file and extracting
Box data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_DUMP_BOX_H
#define STA_DUMP_BOX_H

#include "sta_dump.h"

class StaDumpBox : public StaDump {
 protected:
  virtual void compute_impl(Json &, Set<Str> &) override;
 public:
  using StaDump::StaDump;
  virtual ~StaDumpBox() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_sta_dump_box(py::module &m)
{
  py::class_<StaDumpBox,PyUpdater<StaDumpBox>,StaDump,Starter,Updater,ShPtr<StaDumpBox>>(m, "StaDumpBox")
    .def(py::init<const Str &, int>());
}


#endif