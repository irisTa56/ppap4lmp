/* ---------------------------------------------------------------------
StaDump: stands for Starter reading lammps' Dump file.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "sta_dump.h"

/* ------------------------------------------------------------------ */

StaDump::StaDump(
  const Str &filepath_,
  int timestep_)
{
  filepath = filepath_;
  timestep = timestep_;
}
