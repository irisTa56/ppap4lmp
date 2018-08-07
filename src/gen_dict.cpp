/* ---------------------------------------------------------------------
GenDict: stands for Generator Dictionary containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <algorithm>

#include "gen_dict.h"
#include "utils.h"

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
GenDict::GenDict(
  std::unordered_set<std::shared_ptr<Generator>> generator_set)
{
  std::vector<std::string> key_list;

  for (auto gen : generator_set)
  {
    key_list.push_back(gen->get_datatype());
    generator_dict[key_list.back()] = gen;
  }

  std::sort(key_list.begin(), key_list.end());

  datatype = "Dict(";

  for (const auto &key : key_list)
  {
    datatype += key;

    if (key != key_list.back())
    {
      datatype += ",";
    }
  }

  datatype += ")";

  instance_count++;
  dataname = datatype + "_" + std::to_string(instance_count);

  for (const auto &item : generator_dict)
  {
    merge_update_chain(item.second->get_update_chain());
  }
}

/* ------------------------------------------------------------------ */

const json &GenDict::get_data()
{
  message("You got data from GenDict, " + dataname);
  return data;
}

/* ------------------------------------------------------------------ */

std::shared_ptr<Generator> GenDict::get_generator(
  const std::string &key)
{
  return generator_dict[key];
}

/* ------------------------------------------------------------------ */

const std::unordered_set<std::string> GenDict::get_keys()
{
  std::unordered_set<std::string> tmp;

  for (const auto &item : generator_dict)
  {
    tmp.insert(item.first);
  }

  return tmp;
}