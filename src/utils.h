#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

extern bool ToF_LOGGING;

/* ------------------------------------------------------------------ */

static std::vector<std::string> split(
  const std::string &s, char delim = ' ')
{
  std::vector<std::string> elems;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim))
  {
    if (!item.empty())
    {
        elems.push_back(item);
    }
  }

  return elems;
}

/* ------------------------------------------------------------------ */

static std::vector<std::string> split2(
  const std::string &s, char delim1 = ' ', char delim2 = '\t')
{
  std::vector<std::string> elems;
  std::stringstream ss(s);
  std::string subs, item;

  while (getline(ss, subs, delim1))
  {
    std::stringstream subss(subs);
    while (getline(subss, item, delim2))
    {
      if (!item.empty())
      {
        elems.push_back(item);
      }
    }
  }

  return elems;
}

/* ------------------------------------------------------------------ */

static void logging(const std::string &msg)
{
  if (ToF_LOGGING)
  {
    std::cout << msg << std::endl;
  }
}

/* ------------------------------------------------------------------ */

static void message(const std::string &msg)
{
  std::cout << msg << std::endl;
}

/* ------------------------------------------------------------------ */

static void runtime_error(const std::string &msg)
{
  std::cout << msg << std::endl;
  exit(1);
}

/* ------------------------------------------------------------------ */

template <class T>
static std::string make_dataname(const std::string &datatype, T *ptr)
{
  std::stringstream ss;
  ss << ptr;
  return datatype + "_" + ss.str();
}

/* ------------------------------------------------------------------ */

static const nlohmann::json check_key(
  const nlohmann::json &data, const nlohmann::json &key)
{
  auto key_list = key.is_array() ? key : nlohmann::json({key});

  std::unordered_map<std::string,int> counts;

  for (const auto &k : key_list)
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

    for (const auto &k : key_list)
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

  nlohmann::json tmp;

  if (key.is_array())
  {
    for (const auto &k : key)
    {
      tmp.push_back(bool(counts[k]));
    }
  }
  else
  {
    tmp = bool(counts[key]);
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

static const std::unordered_map<nlohmann::json,int> get_map_to_index(
  const nlohmann::json &data, const nlohmann::json &key)
{
  std::unordered_map<nlohmann::json,int> tmp;

  if (data.is_array())
  {
    int length = data.size();

    if (key.is_array())
    {
      std::vector<std::string> keys_tmp = key;

      for (int i = 0; i != length; ++i)
      {
        auto &d = data[i];

        nlohmann::json arr;

        for (const auto &k : keys_tmp)
        {
          arr.push_back(d[k]);
        }

        tmp[arr] = i;
      }
    }
    else
    {
      std::string key_tmp = key;

      for (int i = 0; i != length; ++i)
      {
        tmp[data[i][key_tmp]] = i;
      }
    }
  }
  else
  {
    message("Map to index cannot be created for non-array or null");
  }

  if (tmp.size() != data.size())
  {
    runtime_error("Map to index is not bijection");
  }

  return tmp;
}

#endif