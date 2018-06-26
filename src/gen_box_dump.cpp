/* ---------------------------------------------------------------------
GenBoxDump: stands for Generator of Box from lammps' Dump file.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <fstream>

#include "gen_box_dump.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

GenBoxDump::GenBoxDump(
  const std::string &filepath_, int timestep_) : GenBox()
{
  filepath = filepath_;
  timestep = timestep_;
}

/* ------------------------------------------------------------------ */

GenBoxDump::GenBoxDump(
  const std::string &filepath_, int timestep_,
  const std::string &suffix) : GenBox(suffix)
{
  filepath = filepath_;
  timestep = timestep_;
}

/* ------------------------------------------------------------------ */

void GenBoxDump::generate()
{
  std::ifstream ifs(filepath);
  std::string line;
  bool timestep_matches = false;
  int n_skip = 0;

  if (!ifs.is_open())
  {
    runtime_error("No such a file: " + filepath);
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
    else if (line.find("ITEM: NUMBER OF ATOMS") == 0 && !timestep_matches)
    {
      std::getline(ifs, line);
      n_skip = std::stoi(line);
    }
    else if (line.find("ITEM: BOX BOUNDS") == 0 && timestep_matches)
    {
      auto strs = split(line);

      data["periodic_x"] = strs[3] == "pp" ? true : false;
      data["periodic_y"] = strs[4] == "pp" ? true : false;
      data["periodic_z"] = strs[5] == "pp" ? true : false;

      for (std::string dim : {"x", "y", "z"})
      {
        std::getline(ifs, line);
        auto strs = split(line);

        data["min_"+dim] = std::stod(strs[0]);
        data["max_"+dim] = std::stod(strs[1]);
      }

      break;
    }
    else if (line.find("ITEM: ATOMS") == 0)
    {
      for (int i = 0; i < n_skip; ++i)
      {
        std::getline(ifs, line);
      }
    }
  }
}
