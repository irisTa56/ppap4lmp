/* ---------------------------------------------------------------------
InvOMP: stands for Invoker using OpenMP.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "inv_omp.h"
#include "../utils/message.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void InvOMP::execute_impl()
{
  #ifdef _OPENMP
  ut::log(
    "Max number of threads = " + std::to_string(omp_get_max_threads()));
  #endif

  bool end = false;

  Str error_msg;

  #pragma omp parallel private(end)
  {
    while (!end)
    {
      end = true;

      try  // Exception must be catched in the OpenMP scope
      {
        for (const auto &p : processors)
        {
          end = end && p->run();
        }
      }
      catch (std::runtime_error &e)
      {
        /* NOTE:
          Older error messages will be overwritten by newer one.
        */
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
