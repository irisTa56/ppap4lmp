/*!
  @file src/starters/sta_dump_atoms.cpp
  @brief This file has an implementation of StaDumpAtoms class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#include <fstream>
#include <tuple>

#include "sta_dump_atoms.h"
#include "../utils/runtime_error.h"
#include "../utils/split.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void StaDumpAtoms::compute_impl(
  Json &data,
  JsonToVoidFunc check_required_keys,
  JsonToBoolFunc check_optional_keys)
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

        Vec<bool> is_int_vector;

        for (const auto &s : ut::split(line))
        {
          // NOTE: If string containes '.', it is converted to float.
          is_int_vector.push_back(s.find(".") == Str::npos);
        }

        // read & set data from the 1st line

        auto &d = data.front();

        auto strs = ut::split(line);

        for (int i = 0; i != is_int_vector.size(); ++i)
        {
          if (is_int_vector[i])
          {
            d[keys[i]] = std::stoi(strs[i]);
          }
          else
          {
            d[keys[i]] = std::stod(strs[i]);
          }
        }

        // read & set data from the remaining lines

        // each tuple contains info of key, int/float, delimiter
        Vec<std::tuple<Str, bool, char>> tuples(is_int_vector.size());
        for (int i = 0; i < tuples.size(); ++i)
        {
          tuples[i] = std::make_tuple(
            keys[i], is_int_vector[i], i+1 == tuples.size() ? '\n' : ' ');
        }

        for (auto it = data.begin()+1; it != data.end(); ++it)
        {
          for (auto jt = tuples.cbegin(); jt != tuples.cend(); ++jt)
          {
            Str str;

            while (str.empty())
            {
              std::getline(ifs, str, std::get<2>(*jt));
            }

            if (std::get<1>(*jt))
            {
              (*it)[std::get<0>(*jt)] = std::stoi(str);
            }
            else
            {
              (*it)[std::get<0>(*jt)] = std::stod(str);
            }
          }
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
