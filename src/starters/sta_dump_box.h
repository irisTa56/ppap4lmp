/* ---------------------------------------------------------------------
StaDumpBox: stands for Starter reading lammps' Dump file and extracting
Box data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_DUMP_BOX_H
#define STA_DUMP_BOX_H

#include <starters/sta_dump.h>

class StaDumpBox : public StaDump {
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  using StaDump::StaDump;
  virtual ~StaDumpBox() = default;
};

#endif