#include <iostream>

#include "message.h"

namespace ut = utils;

bool ToF_LOGGING = false;

/* ------------------------------------------------------------------ */

void ut::_message(
  const Str &msg)
{
  #pragma omp critical (stdout)
  {
    std::cout << msg << std::endl;
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

/* ------------------------------------------------------------------ */
