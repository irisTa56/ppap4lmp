/* ---------------------------------------------------------------------
Invoker: is an abstract class to execute processes.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "invoker.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

Invoker::Invoker(
  ShPtr<Processor> proc)
{
  processors = {proc};
  n_processors = processors.size();
}

/* ------------------------------------------------------------------ */

Invoker::Invoker(
  std::vector<ShPtr<Processor>> procs)
{
  processors = procs;
  n_processors = processors.size();
}

/* ------------------------------------------------------------------ */

void Invoker::execute()
{
  try
  {
    for (auto p : processors)
    {
      p->prepare();
    }

    execute_impl();

    for (auto p : processors)
    {
      p->finish();
    }
  }
  catch (std::runtime_error &e)
  {
    logging(e.what());
    return;
  }
}
