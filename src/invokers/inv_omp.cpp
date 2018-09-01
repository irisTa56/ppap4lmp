/* ---------------------------------------------------------------------
InvOMP: stands for Invoker using OpenMP.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "inv_omp.h"
#include "../utils.h"

/* ------------------------------------------------------------------ */

void InvOMP::execute_impl()
{
  #ifdef _OPENMP
  logging(
    "Max number of threads = " + std::to_string(omp_get_max_threads()));
  #endif

  bool end = false;

  Str error_msg;

  #pragma omp parallel private(end)
  {
    while (!end)
    {
      end = true;

      try  // Exception must be catched in OpenMP scope
      {
        for (auto p : processors)
        {
          end = end && p->run();
        }
      }
      catch (std::runtime_error &e)
      {
        error_msg = e.what();
        break;
      }
    }
  }

  if (!error_msg.empty())
  {
    throw std::runtime_error(error_msg);
  }
}
