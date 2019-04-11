/*!
  @file src/invokers/invoker.cpp
  @brief This file has an implementation of Invoker class,
  which executes one or more analysis.
  @author Takayuki Kobayashi
  @date 2018/06/23
*/

#include "invoker.h"
#include "../utils/message.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void Invoker::execute(const Vec<ShPtr<Processor>> &procs)
{
  for (const auto &p : procs)
  {
    p->startup();
  }

  try
  {
    for (const auto &p : procs)
    {
      p->prepare();
    }

    execute_impl(procs);

    for (const auto &p : procs)
    {
      p->finish();
    }
  }
  catch (std::runtime_error &e)
  {
    // NOTE: Error message can also be seen as Python's exception.
    ut::log("ERROR - " + Str(e.what()));
  }
}
