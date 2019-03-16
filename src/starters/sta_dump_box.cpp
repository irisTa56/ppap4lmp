/*!
  @file src/starters/sta_dump_box.cpp
  @brief This file has an implementation of StaDumpBox class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#include <fstream>

#include "sta_dump_box.h"
#include "../utils/runtime_error.h"
#include "../utils/split.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void StaDumpBox::compute_impl(
  Json &data)
{
  std::ifstream ifs(filepath);
  Str line;
  bool timestep_matches = false;
  int n_atoms = 0;

  if (!ifs.is_open())
  {
    ut::runtime_error("No such a file '" + filepath + "'");
  }

  while (std::getline(ifs, line))
  {
    if (line.find("ITEM: TIMESTEP") == 0)
    {
      std::getline(ifs, line);

      if (std::stoi(line) == timestep)
      {
        timestep_matches = true;
      }
    }
    else if (
      line.find("ITEM: NUMBER OF ATOMS") == 0 && !timestep_matches)
    {
      std::getline(ifs, line);
      n_atoms = std::stoi(line);
    }
    else if (line.find("ITEM: BOX BOUNDS") == 0 && timestep_matches)
    {
      auto strs = ut::split(line);

      for (int i = 0; i != 3; ++i)
      {
        auto key = "pbc_" + Str("xyz").substr(i, 1);

        data[key] = strs[3+i] == "pp";
      }

      for (const Str &dim : {"x", "y", "z"})
      {
        std::getline(ifs, line);
        auto strs = ut::split(line);

        data["lo_"+dim] = std::stod(strs[0]);
        data["hi_"+dim] = std::stod(strs[1]);
      }

      break;
    }
    else if (line.find("ITEM: ATOMS") == 0)
    {
      for (int i = 0; i != n_atoms; ++i)
      {
        std::getline(ifs, line);
      }
    }
  }
}

/* ------------------------------------------------------------------ */
