/*!
  @file src/utils/split.h
  @brief This file has a definition of ::utils::split.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef UTILS_SPLIT_H
#define UTILS_SPLIT_H

#include <alias/std.h>

//! Namespace for utility functions.
namespace utils
{
  /*!
    @brief Mimicking Python's `split`.

    @param str
      A string to be splitted.
    @param delim
      A character by which the `str` is splitted.
      Default delimiter is a whitespace.

    @return A ::Vec object containing each part of splitted strings.
  */
  Vec<Str> split(
    const Str &str,
    char delim = ' ');
}

#endif