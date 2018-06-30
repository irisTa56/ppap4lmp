/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <algorithm>

#include <omp.h>

#include "generator.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void Generator::appoint()
{
  for (const auto &item : update_chain)
  {
    item.first->increment_remain();
  }
}

/* ------------------------------------------------------------------ */

void Generator::hello()
{
  for (const auto &item : update_chain)
  {
    item.first->update_data(item.second);
  }
}

/* ------------------------------------------------------------------ */

void Generator::goodbye()
{
  for (const auto &item : update_chain)
  {
    item.first->decrement_remain();
  }
}

/* ------------------------------------------------------------------ */

const std::string &Generator::get_classname()
{
  return classname;
}

/* ------------------------------------------------------------------ */

const std::string &Generator::get_dataname()
{
  return dataname;
}

/* ------------------------------------------------------------------ */

std::shared_ptr<Generator> Generator::get_generator()
{
  return shared_from_this();
}

/* ------------------------------------------------------------------ */

std::shared_ptr<Generator> Generator::set_parser(std::shared_ptr<Updater> upd)
{
  std::vector<UpdatePair> tmp;

  auto gens = upd->get_generators();

  for (const auto gen : gens)
  {
    merge_update_chain(tmp, gen->get_update_chain());
  }

  tmp.push_back(UpdatePair(shared_from_this(), upd));

  update_chain.insert(update_chain.begin(), tmp.begin(), tmp.end());

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

std::shared_ptr<Generator> Generator::append_adder(std::shared_ptr<Updater> upd)
{
  auto gens = upd->get_generators();

  for (const auto gen : gens)
  {
    merge_update_chain(update_chain, gen->get_update_chain());
  }

  update_chain.push_back(UpdatePair(shared_from_this(), upd));

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

const nlohmann::json &Generator::get_data()
{
  return data;
}

/* ------------------------------------------------------------------ */

const nlohmann::json &Generator::get_data_py()
{
  hello();
  return get_data();
}

/* ------------------------------------------------------------------ */

const bool Generator::check_key(const std::string &key)
{
  int count = 0;

  if (data.is_array())
  {
    for (const auto &d : data)
    {
      if (d.find(key) != d.end())
      {
        count++;
      }
    }

    count /= data.size();
  }
  else
  {
    if (data.find(key) != data.end())
    {
      count++;
    }
  }

  return 0 < count ? true : false;
}

/* ------------------------------------------------------------------ */

const bool Generator::check_key_py(const std::string &key)
{
  hello();
  return check_key(key);
}

/* ------------------------------------------------------------------ */

const std::vector<bool> Generator::check_keys(
  const std::vector<std::string> &keys)
{
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
    result.push_back(counts[k]);  // convert <int> to <bool>
  }

  return result;
}

/* ------------------------------------------------------------------ */

const std::vector<bool> Generator::check_keys_py(
  const std::vector<std::string> &keys)
{
  hello();
  return check_keys(keys);
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXi Generator::get_int_vector(
  const std::string &key)
{
  Eigen::VectorXi v(data.is_array() ? data.size() : 1);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i != length; ++i)
    {
      v(i) = data[i][key];
    }
  }
  else
  {
    message("'get_int_vector()' is for array data");
  }

  return v;
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXi Generator::get_int_vector_py(
  const std::string &key)
{
  hello();
  return get_int_vector(key);
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXd Generator::get_double_vector(
  const std::string &key)
{
  Eigen::VectorXd v(data.is_array() ? data.size() : 1);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i != length; ++i)
    {
      v(i) = data[i][key];
    }
  }
  else
  {
    message("'get_double_vector()' is for array data");
  }

  return v;
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXd Generator::get_double_vector_py(
  const std::string &key)
{
  hello();
  return get_double_vector(key);
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXi Generator::get_int_array(
  const std::vector<std::string> &keys)
{
  int n_keys = keys.size();

  Eigen::ArrayXXi a(data.is_array() ? data.size() : 1, n_keys);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i != length; ++i)
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
    message("'get_int_array()' is for array data");
  }

  return a;
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXi Generator::get_int_array_py(
  const std::vector<std::string> &keys)
{
  hello();
  return get_int_array(keys);
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXd Generator::get_double_array(
  const std::vector<std::string> &keys)
{
  int n_keys = keys.size();

  Eigen::ArrayXXd a(data.is_array() ? data.size() : 1, n_keys);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i != length; ++i)
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
    message("'get_double_array()' is for array data");
  }

  return a;
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXd Generator::get_double_array_py(
  const std::vector<std::string> &keys)
{
  hello();
  return get_double_array(keys);
}

/* ------------------------------------------------------------------ */

void Generator::increment_remain()
{
  #pragma omp atomic
  n_remain += 1;
}

/* ------------------------------------------------------------------ */

void Generator::decrement_remain()
{
  #pragma omp critical
  {
    n_remain -= 1;

    if (n_remain == 0)
    {
      data.clear();
      data = nullptr;

      message(dataname + " has been deleted");
    }
    else if (n_remain < 0)
    {
      runtime_error(dataname + ": Invalid data use is detected");
    }
  }
}

/* ------------------------------------------------------------------ */

void Generator::update_data(std::shared_ptr<Updater> upd)
{
  #pragma omp critical
  upd->compute(data);
}

/* ------------------------------------------------------------------ */

void Generator::merge_update_chain(
  std::vector<UpdatePair> &u, const std::vector<UpdatePair> &v)
{
  for (auto itr = v.begin(); itr != v.end(); ++itr)
  {
    if (std::find(u.begin(), u.end(), *itr) == u.end())
    {
      for (auto jtr = u.begin(); jtr != u.end(); ++jtr)
      {
        bool match = false;

        for (auto ktr = itr+1; ktr != v.end(); ++ktr)
        {
          if (*ktr == *jtr)
          {
            match = true;
            break;
          }
        }

        if (match)
        {
          u.insert(jtr, *itr);
          break;
        }
      }
    }
  }
}

/* ------------------------------------------------------------------ */

const std::vector<UpdatePair> &Generator::get_update_chain()
{
  return update_chain;
}

/* ------------------------------------------------------------------ */

void Generator::check_keys_one(
  std::unordered_map<std::string,int> &counts, const nlohmann::json &d)
{
  auto end = d.end();

  for (auto &item : counts)
  {
    if (d.find(item.first) != end)
    {
      item.second++;
    }
  }
}
