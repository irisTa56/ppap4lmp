/* ---------------------------------------------------------------------
StaDumpBox: stands for Starter reading lammps' Dump file and extracting
Box data (supposed to be used by GenBox).

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_DUMP_BOX_H
#define STA_DUMP_BOX_H

#include "sta_dump.h"

class StaDumpBox : public StaDump {
 public:
  StaDumpBox(const std::string &, int);
  virtual ~StaDumpBox() = default;
 protected:
  virtual void compute_impl(nlohmann::json &) override;
};

/* ------------------------------------------------------------------ */
// for pubind11

static void pybind_sta_dump_box(py::module &m)
{
  py::class_<StaDumpBox,PyUpdater<StaDumpBox>,StaDump,Starter,Updater,std::shared_ptr<StaDumpBox>>(m, "StaDumpBox")
    .def(py::init<const std::string &, int>());
}

#endif