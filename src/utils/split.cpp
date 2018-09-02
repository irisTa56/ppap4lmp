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
/* Not need for now
Vec<Str> ut::split2(
  const Str &str,
  char delim1,
  char delim2)
{
  Vec<Str> tmp;

  std::stringstream ss1(str);
  Str item1;

  while (getline(ss1, item1, delim1))
  {
    std::stringstream ss2(item1);
    Str item2;

    while (getline(ss2, item2, delim2))
    {
      if (!item2.empty())
      {
        tmp.push_back(item2);
      }
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */