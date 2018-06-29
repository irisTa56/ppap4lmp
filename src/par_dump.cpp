/* ---------------------------------------------------------------------
ParDump: stands for Parser to read lammps' Dump file.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "par_dump.h"

/* ------------------------------------------------------------------ */

ParDump::ParDump(const std::string &filepath_, int timestep_)
{
  filepath = filepath_;
  timestep = timestep_;
}
