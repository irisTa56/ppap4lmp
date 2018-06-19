/* ---------------------------------------------------------------------
This file is for Processor class.

create: 2018/06/18 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "processor.h"

/* ------------------------------------------------------------------ */

Processor::Processor(Extractor *extr) {

  extractors.push_back(extr);
  length = extractors.size();

}

/* ------------------------------------------------------------------ */

Processor::Processor(std::vector<Extractor *> extrs) {

  extractors = extrs;
  length = extractors.size();

}

/* ------------------------------------------------------------------ */

int Processor::get_length() {

  return length;

}