/* ---------------------------------------------------------------------
This file is for Invoker class.

create: 2018/06/18 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "invoker.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

Invoker::Invoker(Processor *proc) {

  processors.push_back(proc);
  n_iteration = proc->get_length();

}

/* ------------------------------------------------------------------ */

Invoker::Invoker(std::vector<Processor *> procs) {

  processors = procs;
  n_iteration = procs[0]->get_length();

  for(Processor *p : processors) {
    if (n_iteration != p->get_length()) {
      runtime_error("Number of Data (Extractor) in the Processors should be equal");
    }
  }

}
