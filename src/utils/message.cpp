/*!
  @file src/utils/message.cpp
  @brief This file has implementations of messaging functions.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#include <alias/pybind.h>

#include "message.h"

namespace ut = utils;

bool ToF_LOGGING = false;

/* ------------------------------------------------------------------ */

void ut::_message(
  const Str &msg)
{
  #pragma omp critical (pyprint)
  {
    py::print(msg);
  }
}

/* ------------------------------------------------------------------ */

void ut::log(
  const Str &msg)
{
  if (ToF_LOGGING)
  {
    ut::_message(msg);
  }
}

/* ------------------------------------------------------------------ */

void ut::warning(
  const Str &msg)
{
  ut::_message("WARNING - " + msg);
}

/* ------------------------------------------------------------------ */

void ut::log_switch(
  bool input)
{
  ToF_LOGGING = input;
}
