/*!
  @file src/invokers/inv_omp.cpp
  @brief This file has an implementation of InvOMP class,
  which is a subclass of Invoker class.
  @author Takayuki Kobayashi
  @date 2018/06/23
*/

#include "inv_omp.h"
#include "../utils/message.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void InvOMP::execute_impl(const Vec<ShPtr<Processor>> &procs)
{
  #ifdef _OPENMP
  ut::log(
    "Max number of threads = " + std::to_string(omp_get_max_threads()));
  #endif

  Str error_msg;

  #pragma omp parallel
  {
    while (true)
    {
      try
      {
        bool finish_loop = true;

        for (const auto &p : procs)
        {
          /* NOTE:
            Exit the while loop only if all the processors have finished
            thier computation.
          */
          finish_loop &= p->run();
        }

        if (finish_loop) break;
      }
      // NOTE: Exception must be caught in the same scope.
      catch (std::runtime_error &e)
      {
        #pragma omp critical (inv_omp)
        {
          /* NOTE:
            Older error messages might be overwritten by newer one.
          */
          error_msg = e.what();
        }

        break;
      }
    }
  }

  if (!error_msg.empty())
  {
    throw std::runtime_error(error_msg);
  }
}
