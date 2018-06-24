#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include <pybind11/pybind11.h>

/*=== split ===*/

static std::vector<std::string> split(
  const std::string &s, char delim = ' ') {

  std::vector<std::string> elems;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim)) {
    if (!item.empty()) { elems.push_back(item); }
  }

  return elems;

}

// split by spaces and tabs
static std::vector<std::string> split2(
  const std::string &s, char delim1 = ' ', char delim2 = '\t') {

  std::vector<std::string> elems;
  std::stringstream ss(s);
  std::string subs, item;

  while (getline(ss, subs, delim1)) {
    std::stringstream subss(subs);
    while (getline(subss, item, delim2)) {
      if (!item.empty()) { elems.push_back(item); }
    }
  }

  return elems;

}

/*=== map ===*/

/*
template<typename ELEM, typename MAP>
static std::vector<ELEM> mapfunc(
  const std::vector<ELEM> &src, MAP func) {

  std::vector<ELEM> result;
  for (int i = 0; i < src.size(); i++) {
    result.push_back(func(src[i]));
  }

  return result;

}
*/

/*=== slice ===*/

/*
template<typename ELEM>
static std::vector<ELEM> slice(
  const std::vector<ELEM> &v, int m, int n) {

    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<ELEM> vec(first, last);

    return vec;

}
*/

/*=== message ===*/

static void message(const std::string &msg) {

  std::cout << msg << std::endl;

}

static void runtime_error(const std::string &msg) {

  std::cout << msg << std::endl;
  exit(1);

}

#endif