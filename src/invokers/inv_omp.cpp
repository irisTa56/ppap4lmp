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

      try
      {
        for (const auto &p : processors)
        {
          end = end && p->run();
        }
      }
      // Exception must be catched in the same scope.
      catch (std::runtime_error &e)
      {
        #pragma omp critical (inv_omp)
        {
          // Older error messages will be overwritten by newer one.
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

/* ------------------------------------------------------------------ */
