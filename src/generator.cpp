/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "generator.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void Generator::append_adder(std::shared_ptr<Adder> add)
{
  adders.push_back(add);
}

/* ------------------------------------------------------------------ */

void Generator::appoint()
{
  n_appointment += 1;
}

/* ------------------------------------------------------------------ */

void Generator::goodbye()
{
  #pragma omp critical
  {
    n_appointment -= 1;

    if (n_appointment == 0)
    {
      data.clear();
      data = nullptr;

      message(dataname + " has been deleted");
    }
    else if (n_appointment < 0)
    {
      runtime_error(dataname + ": Invalid data use is detected");
    }
  }
}

/* ------------------------------------------------------------------ */

const std::vector<int> Generator::count_keys(
  const std::vector<std::string> &keys, bool check_only_front)
{
  check_data();

  int length = keys.size();
  std::unordered_map<std::string,int> counts;

  for (const auto &k : keys)
  {
    counts[k] = 0;
  }

  if (data.is_array())
  {
    if (check_only_front)
    {
      count_keys_one(counts, data.front());
    }
    else
    {
      for (const auto &d : data)
      {
        count_keys_one(counts, d);
      }

      int data_size = data.size();

      for (const auto &k : keys)
      {
        counts[k] /= data_size;
      }
    }
  }
  else
  {
    count_keys_one(counts, data);
  }

  std::vector<int> result;

  for (const auto &k : keys)
  {
    result.push_back(counts[k]);
  }

  return result;
}

/* ------------------------------------------------------------------ */

const nlohmann::json &Generator::get_data()
{
  check_data();

  return data;
}

/* ------------------------------------------------------------------ */

void Generator::check_data()
{
  #pragma omp critical
  {
    generate();

    for (auto a : adders)
    {
      a->compute(data, dataname);
    }
  }
}

/* ------------------------------------------------------------------ */

void Generator::count_keys_one(
  std::unordered_map<std::string,int> &counts, const nlohmann::json &data)
{
  for (auto &item : counts)
  {
    int count_tmp = data.count(item.first);

    if (1 < count_tmp)
    {
      message("Duplicate data key: " + item.first);
    }

    item.second += count_tmp;
  }
}