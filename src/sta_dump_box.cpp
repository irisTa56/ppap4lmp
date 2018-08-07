/* ---------------------------------------------------------------------
StaDumpBox: stands for Starter reading lammps' Dump file and extracting
Box data (supposed to be used by GenBox).

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <fstream>

#include "sta_dump_box.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

StaDumpBox::StaDumpBox(
  const std::string &filepath_,
  int timestep_) : StaDump(filepath_, timestep_)
{
  datatype_to_be_initialized = "Box";
}

/* ------------------------------------------------------------------ */

void StaDumpBox::compute_impl(json &data)
{
  std::ifstream ifs(filepath);
  std::string line;
  bool timestep_matches = false;
  int n_atoms = 0;

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
    else if (
      line.find("ITEM: NUMBER OF ATOMS") == 0 && !timestep_matches)
    {
      std::getline(ifs, line);
      n_atoms = std::stoi(line);
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
      for (int i = 0; i != n_atoms; ++i)
      {
        std::getline(ifs, line);
      }
    }
  }
}
