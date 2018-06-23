/* ---------------------------------------------------------------------
InvOMP: stands for Invoker using OpenMP.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <omp.h>

#include "inv_omp.h"

/* ------------------------------------------------------------------ */

void InvOMP::execute_impl() {

  #pragma omp parallel for schedule(dynamic)
  for (int itr = 0; itr < n_generators; ++itr) {
    for(auto p : processors) {
      p->run(itr);
    }
  }

}
