/* ---------------------------------------------------------------------
InvOMP: stands for Invoker using OpenMP.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <omp.h>

#include "inv_omp.h"

/* ------------------------------------------------------------------ */

void InvOMP::execute_impl()
{
  #ifdef _OPENMP
  std::cout << "Max number of threads = " << omp_get_max_threads() << std::endl;
  #endif

  #pragma omp parallel for schedule(dynamic)
  for (int itr = 0; itr < n_generators; ++itr)
  {
    for(auto p : processors)
    {
      p->run(itr);
    }
  }
}
