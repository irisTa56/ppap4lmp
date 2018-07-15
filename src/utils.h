#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

static bool check_key(const json &data, const json &key)
{
  auto key_list = key.is_array() ? key : json({key});

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

  bool tmp = true;

  for (const std::string &k : key_list)
  {
    if (!bool(counts[k]))
    {
      tmp = false;
      break;
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

static json get_partial_json(const json &data, const json &key)
{
  std::vector<std::string> key_list = key.is_array() ? key : json({key});

  json tmp;

  if (data.is_array())
  {
    for (const auto &d : data)
    {
      json elem;

      for (const auto &k : key_list)
      {
        elem[k] = d[k];
      }

      tmp.push_back(elem);
    }
  }
  else
  {
    for (const auto &k : key_list)
    {
      tmp[k] = data[k];
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

static std::unordered_map<json,int> get_map_to_index(
  const json &data, const json &key)
{
  std::unordered_map<json,int> tmp;

  if (data.is_array())
  {
    int length = data.size();

    if (key.is_array())
    {
      std::vector<std::string> keys_tmp = key;

      for (int i = 0; i != length; ++i)
      {
        auto &d = data[i];

        json arr;

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