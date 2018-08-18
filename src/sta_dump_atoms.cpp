/* ---------------------------------------------------------------------
StaDumpAtoms: stands for Starter reading lammps' Dump file and
extracting Atoms data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <fstream>

#include "sta_dump_atoms.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void StaDumpAtoms::compute_impl(Json &data, Set<Str> &datakeys)
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
    else if (line.find("ITEM: NUMBER OF ATOMS") == 0)
    {
      std::getline(ifs, line);
      n_atoms = std::stoi(line);
    }
    else if (line.find("ITEM: ATOMS") == 0)
    {
      if (timestep_matches)
      {
        auto keys = split(line);
        keys.erase(keys.begin(), keys.begin()+2);

        std::getline(ifs, line);

        auto is_int_vector = get_is_int_vector(line);
        int size = is_int_vector.size();

        for (int i = 0; i != n_atoms; ++i)
        {
          auto &a = data[i];
          auto strs = split(line);

          for (int j = 0; j != size; ++j)
          {
            if (is_int_vector[j])
            {
              a[keys[j]] = std::stoi(strs[j]);
            }
            else
            {
              a[keys[j]] = std::stod(strs[j]);
            }
          }

          std::getline(ifs, line);
        }

        datakeys.insert(keys.begin(), keys.end());

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

  if (check_containment<Str>(datakeys, "id"))
  {
    ascending_sort_by("id", data);
  }
}

/* ------------------------------------------------------------------ */

const List<bool> StaDumpAtoms::get_is_int_vector(const Str &line)
{
  List<bool> is_int;

  for (const auto &s : split(line))
  {
    is_int.push_back(s.find(".") == Str::npos ? true : false);
  }

  return is_int;
}
