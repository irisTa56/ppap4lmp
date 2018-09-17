/*!
  @file src/utils/split.cpp
  @brief This file has an implementation of ::utils::split.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#include <sstream>

#include "split.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

Vec<Str> ut::split(
  const Str &str,
  char delim)
{
  Vec<Str> tmp;

  std::stringstream ss(str);
  Str item;

  while (getline(ss, item, delim))
  {
    if (!item.empty())
    {
      tmp.push_back(item);
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */