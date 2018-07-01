#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <typeinfo>
#include <cxxabi.h>

/*=== split ===*/

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

// split by spaces and tabs
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

/*=== message ===*/

static void message(const std::string &msg)
{
  std::cout << msg << std::endl;
}

static void runtime_error(const std::string &msg)
{
  std::cout << msg << std::endl;
  exit(1);
}

/*=== dataname ===*/

template <class T>
static std::string make_dataname(const std::string &datatype, T *ptr)
{
  std::stringstream ss;
  ss << ptr;
  return datatype + "_" + ss.str();
}

#endif