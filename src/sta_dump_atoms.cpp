/* ---------------------------------------------------------------------
StaDumpAtoms: stands for Starter reading lammps' Dump file and
extracting Atoms data (supposed to be used by GenAtoms).

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <fstream>

#include "sta_dump_atoms.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

StaDumpAtoms::StaDumpAtoms(
  const std::string &filepath_,
  int timestep_) : StaDump(filepath_, timestep_)
{
  datatype_to_be_initialized = "Atoms";
}

/* ------------------------------------------------------------------ */

void StaDumpAtoms::compute_impl(nlohmann::json &data)
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

        auto is_int = get_is_int_vector(line);
        int length = is_int.size();

        for (int i = 0; i != n_atoms; ++i)
        {
          auto &a = data[i];
          auto strs = split(line);

          for (int j = 0; j != length; ++j)
          {
            if (is_int[j])
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

const std::vector<bool> StaDumpAtoms::get_is_int_vector(
  const std::string &line)
{
  std::vector<bool> is_int;

  auto strs = split(line);

  for (const auto &s : strs)
  {
    is_int.push_back(s.find(".") == std::string::npos ? true : false);
  }

  return is_int;
}
