#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>

#include "aliases.h"

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
    std::cout << msg << std::endl;
  }
}

/* ------------------------------------------------------------------ */

static void message(const Str &msg)
{
  std::cout << msg << std::endl;
}

/* ------------------------------------------------------------------ */

static void runtime_error(const Str &msg)
{
  std::cout << msg << std::endl;
  PyErr_SetString(PyExc_RuntimeError, msg.c_str());
}

/* ------------------------------------------------------------------ */

static Json get_partial_Json(const Json &data, const Json &key)
{
  List<Str> key_list = key.is_array() ? key : Json({key});

  Json tmp;

  if (data.is_array())
  {
    for (const auto &d : data)
    {
      Json elem;

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

static Dict<Json,int> get_map_to_index(
  const Json &data, const Json &key)
{
  Dict<Json,int> tmp;

  if (data.is_array())
  {
    int length = data.size();

    if (key.is_array())
    {
      for (int i = 0; i != length; ++i)
      {
        auto &d = data[i];
        Json arr;

        for (const Str &k : key)
        {
          arr.push_back(d[k]);
        }

        tmp[arr] = i;
      }
    }
    else
    {
      for (int i = 0; i != length; ++i)
      {
        tmp[data[i][key.get<Str>()]] = i;
      }
    }
  }
  else
  {
    message("Map to index cannot be created for non-array/null data");
  }

  if (tmp.size() != data.size())
  {
    runtime_error("Map to index is not bijection");
  }

  return tmp;
}

#endif