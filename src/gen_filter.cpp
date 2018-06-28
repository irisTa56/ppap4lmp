/* ---------------------------------------------------------------------
GenFilter: stands for Generator for Filtered data.

create: 2018/06/28 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "gen_filter.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

GenFilter::GenFilter(std::shared_ptr<Generator> original_)
{
  original = original_;

  std::stringstream ss;
  ss << this;
  dataname = original->get_dataname() + "_" + ss.str();
}

/* ------------------------------------------------------------------ */

void GenFilter::appoint()
{
  Generator::appoint();
  original->appoint();
}
