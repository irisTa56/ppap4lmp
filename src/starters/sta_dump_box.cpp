/* ---------------------------------------------------------------------
StaDumpBox: stands for Starter reading lammps' Dump file and extracting
Box data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <fstream>

#include "sta_dump_box.h"
#include "../utils/runtime_error.h"
#include "../utils/split.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void StaDumpBox::compute_impl(
  Json &data,
  DataKeys &datakeys)
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
      Vec<Str> xyz = {"x", "y", "z"};

      auto strs = ut::split(line);

      for (int i = 0; i != 3; ++i)
      {
        auto key = "periodic_" + xyz[i];

        data[key] = strs[3+i] == "pp";
        datakeys.add(key);
      }

      for (const auto &dim : xyz)
      {
        std::getline(ifs, line);
        auto strs = ut::split(line);

        data["lo_"+dim] = std::stod(strs[0]);
        data["hi_"+dim] = std::stod(strs[1]);

        datakeys.add({"lo_"+dim, "hi_"+dim});
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
