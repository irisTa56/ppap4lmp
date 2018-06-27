/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "generator.h"
#include "utils.h"

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

void Generator::append_adder(std::shared_ptr<Adder> add)
{
  adders.push_back(add);
}

/* ------------------------------------------------------------------ */

const nlohmann::json &Generator::get_data()
{
  check_data();

  return data;
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXi Generator::get_int_vector(
  const std::string &key)
{
  check_data();

  Eigen::VectorXi v(data.is_array() ? data.size() : 1);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i < length; ++i)
    {
      v(i) = data[i][key];
    }
  }
  else
  {
    v(0) = data[key];
  }

  return v;
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXd Generator::get_double_vector(
  const std::string &key)
{
  check_data();

  Eigen::VectorXd v(data.is_array() ? data.size() : 1);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i < length; ++i)
    {
      v(i) = data[i][key];
    }
  }
  else
  {
    v(0) = data[key];
  }

  return v;
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXi Generator::get_int_array(
  const std::vector<std::string> &keys)
{
  check_data();

  int n_keys = keys.size();

  Eigen::ArrayXXi a(data.is_array() ? data.size() : 1, n_keys);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i < length; ++i)
    {
      auto &d = data[i];

      for (int j = 0; j < n_keys; ++j)
      {
        a(i, j) = d[keys[j]];
      }
    }
  }
  else
  {
    for (int j = 0; j < n_keys; ++j)
    {
      a(0, j) = data[keys[j]];
    }
  }

  return a;
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXd Generator::get_double_array(
  const std::vector<std::string> &keys)
{
  check_data();

  int n_keys = keys.size();

  Eigen::ArrayXXd a(data.is_array() ? data.size() : 1, n_keys);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i < length; ++i)
    {
      auto &d = data[i];

      for (int j = 0; j < n_keys; ++j)
      {
        a(i, j) = d[keys[j]];
      }
    }
  }
  else
  {
    for (int j = 0; j < n_keys; ++j)
    {
      a(0, j) = data[keys[j]];
    }
  }

  return a;
}

/* ------------------------------------------------------------------ */

const std::vector<bool> Generator::check_keys(
  const std::vector<std::string> &keys)
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
    for (const auto &d : data)
    {
      check_keys_one(counts, d);
    }

    int data_size = data.size();

    for (const auto &k : keys)
    {
      counts[k] /= data_size;
    }
  }
  else
  {
    check_keys_one(counts, data);
  }

  std::vector<bool> result;

  for (const auto &k : keys)
  {
    result.push_back(counts[k]);
  }

  return result;
}

/* ------------------------------------------------------------------ */

const std::vector<int> Generator::count_keys(
  const std::vector<std::string> &keys)
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

void Generator::check_keys_one(
  std::unordered_map<std::string,int> &counts,
  const nlohmann::json &data)
{
  auto end = data.end();

  for (auto &item : counts)
  {
    if (data.find(item.first) != end)
    {
      item.second++;
    }
  }
}

/* ------------------------------------------------------------------ */

void Generator::count_keys_one(
  std::unordered_map<std::string,int> &counts,
  const nlohmann::json &data)
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