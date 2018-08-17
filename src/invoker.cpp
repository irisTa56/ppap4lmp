/* ---------------------------------------------------------------------
Invoker: is an abstract class to execute processes.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "invoker.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

Invoker::Invoker(ShPtr<Processor> proc)
{
  processors = {proc};
  n_processors = processors.size();
}

/* ------------------------------------------------------------------ */

Invoker::Invoker(std::vector<ShPtr<Processor>> procs)
{
  processors = procs;
  n_processors = processors.size();
}

/* ------------------------------------------------------------------ */

void Invoker::execute()
{
  if (ERROR_OCCURED)
  {
    ERROR_OCCURED = false;
    logging("'ERROR_OCCURED' was reset to false");
  }

  for (auto p : processors)
  {
    p->prepare();
  }

  if (ERROR_OCCURED)
  {
    return;
  }

  execute_impl();

  if (ERROR_OCCURED)
  {
    return;
  }

  for (auto p : processors)
  {
    p->finish();
  }
}
