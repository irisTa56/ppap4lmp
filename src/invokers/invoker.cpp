/* ---------------------------------------------------------------------
Invoker: is an abstract class to execute processes.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "invoker.h"
#include "../utils/message.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

Invoker::Invoker(
  const ShPtr<Processor> &proc)
{
  processors = {proc};
  n_processors = processors.size();
}

/* ------------------------------------------------------------------ */

Invoker::Invoker(
  const std::vector<ShPtr<Processor>> &procs)
{
  processors = procs;
  n_processors = processors.size();
}

/* ------------------------------------------------------------------ */

void Invoker::execute()
{
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
