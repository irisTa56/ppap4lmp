/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "gen_element.h"
#include "utils.h"

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
GenElement::GenElement()
{
  instance_count++;
  dataname = "_" + std::to_string(instance_count);
}

/* ------------------------------------------------------------------ */

const nlohmann::json &GenElement::get_data()
{
  return data;
}

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
std::shared_ptr<Generator> GenElement::set_initial_updater(
  std::shared_ptr<Updater> upd)
{
  upd->initialize_datatype(datatype);
  dataname = datatype + dataname;

  update_chain.insert(
    update_chain.begin(), UpdatePair(shared_from_this(), upd));

  auto gen = upd->get_generator();

  if (gen)
  {
    auto &forward_chain = gen->get_update_chain();

    update_chain.insert(
      update_chain.begin(), forward_chain.begin(), forward_chain.end());
  }

  return shared_from_this();
}

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
std::shared_ptr<Generator> GenElement::append_updater(
  std::shared_ptr<Updater> upd)
{
  if (!upd->is_callable(datatype))
  {
    runtime_error(dataname + " cannot call Updater");
  }

  auto gen = upd->get_generator();

  if (gen)
  {
    merge_update_chain(gen->get_update_chain());
  }

  update_chain.push_back(UpdatePair(shared_from_this(), upd));

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

const bool GenElement::check_key(
  const std::string &key)
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

const std::vector<bool> GenElement::check_keys(
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
      auto end = d.end();

      for (auto &item : counts)
      {
        if (d.find(item.first) != end)
        {
          item.second++;
        }
      }
    }

    int data_size = data.size();

    for (const auto &k : keys)
    {
      counts[k] /= data_size;
    }
  }
  else
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

  std::vector<bool> result;

  for (const auto &k : keys)
  {
    result.push_back(counts[k]);
  }

  return result;
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXi GenElement::get_int_vector(
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

const Eigen::VectorXd GenElement::get_double_vector(
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

const Eigen::ArrayXXi GenElement::get_int_array(
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

      for (int j = 0; j != n_keys; ++j)
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

const Eigen::ArrayXXd GenElement::get_double_array(
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

      for (int j = 0; j != n_keys; ++j)
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

const nlohmann::json &GenElement::get_data_py()
{
  hello();
  return get_data();
}

/* ------------------------------------------------------------------ */

const bool GenElement::check_key_py(
  const std::string &key)
{
  hello();
  return check_key(key);
}

/* ------------------------------------------------------------------ */

const std::vector<bool> GenElement::check_keys_py(
  const std::vector<std::string> &keys)
{
  hello();
  return check_keys(keys);
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXi GenElement::get_int_vector_py(
  const std::string &key)
{
  hello();
  return get_int_vector(key);
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXd GenElement::get_double_vector_py(
  const std::string &key)
{
  hello();
  return get_double_vector(key);
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXi GenElement::get_int_array_py(
  const std::vector<std::string> &keys)
{
  hello();
  return get_int_array(keys);
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXd GenElement::get_double_array_py(
  const std::vector<std::string> &keys)
{
  hello();
  return get_double_array(keys);
}
