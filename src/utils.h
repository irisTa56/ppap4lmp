#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <iostream>
#include <sstream>

#include "aliases.h"

extern bool ERROR_OCCURED;
extern bool ToF_LOGGING;

/* ------------------------------------------------------------------ */

static List<Str> split(const Str &s, char delim = ' ')
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
  const Str &s, char delim1 = ' ', char delim2 = '\t')
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

static void logging(const Str &msg)
{
  if (ToF_LOGGING)
  {
    #pragma omp critical (io)
    {
      std::cout << msg << std::endl;
    }
  }
}

/* ------------------------------------------------------------------ */

static void message(const Str &msg)
{
  #pragma omp critical (io)
  {
    std::cout << msg << std::endl;
  }
}

/* ------------------------------------------------------------------ */

static void runtime_error(const Str &msg)
{
  logging(msg);

  #pragma omp critical
  {
    PyErr_SetString(PyExc_RuntimeError, msg.c_str());
    ERROR_OCCURED = true;
  }
}

/* ------------------------------------------------------------------ */

template <typename T>
static bool check_containment(const Set<T> &set, const T &el)
{
  if (set.find(el) == set.end())
  {
    return false;
  }
  else
  {
    return true;
  }
}

/* ------------------------------------------------------------------ */

template <typename T>
static bool check_containment(const Set<T> &set, const Set<T> &els)
{
  bool tmp = true;

  for (const auto &el : els)
  {
    if (set.find(el) == set.end())
    {
      tmp = false;
      break;
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

static Json get_partial_json(const Json &data, const Str &key)
{
  Json tmp;

  if (data.is_array())
  {
    for (const auto &d : data)
    {
      tmp.push_back({key, d[key]});
    }
  }
  else
  {
    tmp[key] = data[key];
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

static Json get_partial_json(const Json &data, const Set<Str> &keys)
{
  Json tmp;

  if (data.is_array())
  {
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
  const Json &data, const Str &key)
{
  Dict<Json,int> tmp;

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i != length; ++i)
    {
      tmp[data[i][key]] = i;
    }
  }

  if (tmp.size() != data.size())
  {
    runtime_error("Map to index is not bijection");
    return Dict<Json,int>();
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

static Dict<Json,int> get_map_to_index(
  const Json &data, const List<Str> &keys)
{
  Dict<Json,int> tmp;

  if (data.is_array())
  {
    int length = data.size();

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
    return Dict<Json,int>();
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

static void ascending_sort_by(const Str &key, Json &data)
{
  std::sort(
    data.begin(), data.end(),
    [key](auto &a, auto &b)
    {
      return a[key] < b[key];
    });
}

/* ------------------------------------------------------------------ */

static void descending_sort_by(const Str &key, Json &data)
{
  std::sort(
    data.begin(), data.end(),
    [key](auto &a, auto &b)
    {
      return a[key] > b[key];
    });
}

#endif