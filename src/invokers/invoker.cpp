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

Invoker::Invoker(
  const ShPtr<Processor> &proc)
{
  processors = {proc};
}

/* ------------------------------------------------------------------ */

Invoker::Invoker(
  const Vec<ShPtr<Processor>> &procs)
{
  processors = procs;
}

/* ------------------------------------------------------------------ */

void Invoker::execute()
{
  for (const auto &p : processors)
  {
    p->startup();
  }

  try
  {
    for (const auto &p : processors)
    {
      p->prepare();
    }

    execute_impl();

    for (const auto &p : processors)
    {
      p->finish();
    }
  }
  catch (std::runtime_error &e)
  {
    ut::log("ERROR - " + Str(e.what()));
  }
}

/* ------------------------------------------------------------------ */
