/* ---------------------------------------------------------------------
StaDumpBox: stands for Starter reading lammps' Dump file and extracting
Box data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <fstream>

#include "sta_dump_box.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void StaDumpBox::compute_impl(Json &data, Set<Str> &datakeys)
{
  std::ifstream ifs(filepath);
  Str line;
  bool timestep_matches = false;
  int n_atoms = 0;

  if (!ifs.is_open())
  {
    runtime_error("No such a file: " + filepath);
    return;
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

      datakeys.insert({"periodic_x", "periodic_y", "periodic_z"});

      for (Str dim : {"x", "y", "z"})
      {
        std::getline(ifs, line);
        auto strs = split(line);

        data["lo_"+dim] = std::stod(strs[0]);
        data["hi_"+dim] = std::stod(strs[1]);

        datakeys.insert({"lo_"+dim, "hi_"+dim});
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
