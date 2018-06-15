/* ---------------------------------------------------------------------
This file is for Data class.

create: 2018/06/14 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "processor.h"

Processor::Processor() {
  dataname = "";
}

void Processor::execute(const Data &data) {
  dataname = data.get_name();
}

const std::string &Processor::get_result() const {
  return dataname;
}
