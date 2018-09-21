/*!
  @file src/starters/sta_dump.cpp
  @brief This file has an implementation of StaDump class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/06/29
  @details For more details, please see the header file,
  src/starters/sta_dump.h.
*/

#include "sta_dump.h"

/* ------------------------------------------------------------------ */

StaDump::StaDump(
  const Str &filepath_,
  const int timestep_)
{
  filepath = filepath_;
  timestep = timestep_;
}

/* ------------------------------------------------------------------ */
