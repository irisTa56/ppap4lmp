/* ---------------------------------------------------------------------
This file is for InvoOMP class.

create: 2018/06/18 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <omp.h>

#include "invo_omp.h"

/* ------------------------------------------------------------------ */

void InvoOMP::execute() {

  for(Processor *p : processors) {
    p->prepare();
  }

  #pragma omp parallel for schedule(dynamic)
  for (int itr = 0; itr < n_iteration; ++itr) {
    for(Processor *p : processors) {
      p->run(itr);
    }
  }

}
