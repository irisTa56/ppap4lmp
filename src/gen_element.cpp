/* ---------------------------------------------------------------------
GenElement: stands for Generator containing data 'element'.

create: 2018/07/01 by Takayuki Kobayashi
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
  hello();
  return data;
}

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
void GenElement::append_updater(
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

const bool GenElement::check_key(
  const std::string &key)
{
  hello();

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
  hello();

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
  hello();

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
    v(0) = data[key];
    message(dataname + " might be non-array or null (not int_vector)");
  }

  return v;
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXd GenElement::get_double_vector(
  const std::string &key)
{
  hello();

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
    v(0) = data[key];
    message(dataname + " might be non-array or null (not double_vector)");
  }

  return v;
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXi GenElement::get_int_array(
  const std::vector<std::string> &keys)
{
  hello();

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
    for (int j = 0; j != n_keys; ++j)
    {
      a(0, j) = data[keys[j]];
    }
    message(dataname + " might be non-array or null (not int_array)");
  }

  return a;
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXd GenElement::get_double_array(
  const std::vector<std::string> &keys)
{
  hello();

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
    for (int j = 0; j != n_keys; ++j)
    {
      a(0, j) = data[keys[j]];
    }
    message(dataname + " might be non-array or null (not double_array)");
  }

  return a;
}

/* ------------------------------------------------------------------ */

const Map2Index &GenElement::get_map_to_index(const nlohmann::json &keys)
{
  auto new_keys = get_keys_for_map(keys);

  if (new_keys == keys_for_map)
  {
    return map_to_index;
  }
  else
  {
    keys_for_map = new_keys;

    if (!map_to_index.empty())
    {
      map_to_index.clear();
    }
  }

  hello();

  bool key_is_multi = keys_for_map.size() > 1 ? true : false;

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i != length; ++i)
    {
      auto &d = data[i];

      if (key_is_multi)
      {
        nlohmann::json tmp;

        for (const auto &key : keys_for_map)
        {
          tmp.push_back(d[key]);
        }

        map_to_index[tmp] = i;
      }
      else
      {
        map_to_index[d[keys_for_map.front()]] = i;
      }
    }
  }
  else
  {
    message(dataname + " might be non-array or null");
  }

  if (map_to_index.size() != data.size())
  {
    runtime_error("Map to index is not bijection");
  }

  return map_to_index;
}

/* ------------------------------------------------------------------ */

const std::vector<std::string> GenElement::get_keys_for_map(
  const nlohmann::json &keys)
{
  std::vector<std::string> tmp;

  if (keys.is_array())
  {
    for (const auto &key : keys)
    {
      tmp.push_back(key);
    }
  }
  else
  {
    tmp.push_back(keys);
  }

  return tmp;
}