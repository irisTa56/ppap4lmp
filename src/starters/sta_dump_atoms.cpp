/* ---------------------------------------------------------------------
StaDumpAtoms: stands for Starter reading lammps' Dump file and
extracting Atoms data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <fstream>

#include "sta_dump_atoms.h"
#include "../utils/disorder.h"
#include "../utils/runtime_error.h"
#include "../utils/split.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void StaDumpAtoms::compute_impl(
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
    else if (line.find("ITEM: NUMBER OF ATOMS") == 0)
    {
      std::getline(ifs, line);
      n_atoms = std::stoi(line);

      if (timestep_matches)
      {
        data = Json::array();
        data.get_ref<Json::array_t&>().resize(n_atoms);
      }
    }
    else if (line.find("ITEM: ATOMS") == 0)
    {
      if (timestep_matches)
      {
        auto keys = ut::split(line);
        keys.erase(keys.begin(), keys.begin()+2);

        std::getline(ifs, line);

        auto is_int_vector = make_is_int_vector(line);
        auto size = is_int_vector.size();

        for (auto &d : data)
        {
          auto strs = ut::split(line);

          for (int j = 0; j != size; ++j)
          {
            if (is_int_vector[j])
            {
              d[keys[j]] = std::stoi(strs[j]);
            }
            else
            {
              d[keys[j]] = std::stod(strs[j]);
            }
          }

          std::getline(ifs, line);
        }

        datakeys.add(ut::disorder(keys));

        break;
      }
      else
      {
        for (int i = 0; i != n_atoms; ++i)
        {
          std::getline(ifs, line);
        }
      }
    }
  }
}

/* ------------------------------------------------------------------ */

const Vec<bool> StaDumpAtoms::make_is_int_vector(
  const Str &line)
{
  Vec<bool> is_int;

  for (const auto &s : ut::split(line))
  {
    is_int.push_back(s.find(".") == Str::npos);
  }

  return is_int;
}
