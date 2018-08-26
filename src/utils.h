#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "aliases.h"

extern bool ToF_LOGGING;

/* ------------------------------------------------------------------ */

static List<Str> split(
  const Str &s,
  char delim = ' ')
{
  List<Str> elems;
  std::stringstream ss(s);
  Str item;

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

static List<Str> split2(
  const Str &s,
  char delim1 = ' ',
  char delim2 = '\t')
{
  List<Str> elems;
  std::stringstream ss(s);
  Str subs, item;

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

static void message(
  const Str &msg)
{
  #pragma omp critical (io)
  {
    std::cout << msg << std::endl;
  }
}

/* ------------------------------------------------------------------ */

static void logging(
  const Str &msg)
{
  if (ToF_LOGGING)
  {
    message(msg);
  }
}

/* ------------------------------------------------------------------ */

static void runtime_error(
  const Str &msg)
{
  #pragma omp critical (py_runtime_error)
  {
    PyErr_SetString(PyExc_RuntimeError, msg.c_str());
  }

  throw std::runtime_error(msg);
}

/* ------------------------------------------------------------------ */

template <typename T>
static List<std::pair<int,T>> get_indexed_list(
  const List<T> &list)
{
  List<std::pair<int,T>> tmp;

  auto length = list.size();

  for (int i = 0; i != length; ++i)
  {
    tmp.push_back(std::make_pair(i, list[i]));
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

template <typename T>
static bool check_containment(
  const Set<T> &set,
  const T &el)
{
  return set.find(el) != set.end();
}

/* ------------------------------------------------------------------ */

template <typename T>
static bool check_containment(
  const Set<T> &set,
  const Set<T> &els)
{
  for (const auto &el : els)
  {
    if (set.find(el) == set.end())
    {
      return false;
    }
  }

  return true;
}

/* ------------------------------------------------------------------ */

static Json get_partial_json(
  const Json &data,
  const Str &key)
{
  return get_partial_json(data, {key});
}

/* ------------------------------------------------------------------ */

static Json get_partial_json(
  const Json &data,
  const Set<Str> &keys)
{
  Json tmp;

  if (data.is_array())
  {
    tmp = Json::array({});
    tmp.get_ref<Json::array_t&>().reserve(data.size());

    for (const auto &d : data)
    {
      Json elem;

      for (const auto &k : keys)
      {
        elem[k] = d[k];
      }

      tmp.push_back(elem);
    }
  }
  else
  {
    for (const auto &k : keys)
    {
      tmp[k] = data[k];
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

static Dict<Json,int> get_map_to_index(
  const Json &data,
  const Str &key)
{
  Dict<Json,int> tmp;

  if (data.is_array())
  {
    auto length = data.size();

    tmp.reserve(length);

    for (int i = 0; i != length; ++i)
    {
      tmp[data[i][key]] = i;
    }
  }

  if (tmp.size() != data.size())
  {
    runtime_error("Map to index is not bijection");
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

static Dict<Json,int> get_map_to_index(
  const Json &data,
  const List<Str> &keys)
{
  Dict<Json,int> tmp;

  if (data.is_array())
  {
    auto length = data.size();

    tmp.reserve(length);

    for (int i = 0; i != length; ++i)
    {
      auto &d = data[i];

      Json arr;

      for (const Str &key : keys)
      {
        arr.push_back(d[key]);
      }

      tmp[arr] = i;
    }
  }

  if (tmp.size() != data.size())
  {
    runtime_error("Map to index is not bijection");
  }

  return tmp;
}

#endif