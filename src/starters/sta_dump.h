/* ---------------------------------------------------------------------
StaDump: stands for Starter reading lammps' Dump file.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_DUMP_H
#define STA_DUMP_H

#include <starters/starter.h>

class StaDump : public Starter {
 protected:
  int timestep;
  Str filepath;
 public:
  StaDump(
    const Str &filepath_,
    int timestep_);
  virtual ~StaDump() = default;
};

#endif