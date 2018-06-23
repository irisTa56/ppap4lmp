/* ---------------------------------------------------------------------
Invoker: is an abstract class to execute processes.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "invoker.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

Invoker::Invoker(std::shared_ptr<Processor> proc) {

  processors.push_back(proc);
  n_processors = processors.size();

  n_generators = proc->get_n_generators();

}

/* ------------------------------------------------------------------ */

Invoker::Invoker(std::vector<std::shared_ptr<Processor>> procs) {

  processors = procs;
  n_processors = processors.size();

  n_generators = procs[0]->get_n_generators();

  for(auto p : processors) {
    if (n_generators != p->get_n_generators()) {
      runtime_error(
        "Numbers of Data (Generators) in the Processors are different");
    }
  }

}

/* ------------------------------------------------------------------ */

void Invoker::execute() {

  for(auto p : processors) {
    p->prepare();
  }

  execute_impl();

  for(auto p : processors) {
    p->finish();
  }

}

/* ------------------------------------------------------------------ */

int Invoker::get_n_processors() {

  return n_processors;

}
