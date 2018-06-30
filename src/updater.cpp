/* ---------------------------------------------------------------------
Updater: is an abstract class to update data held by Generator.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "updater.h"

/* ------------------------------------------------------------------ */

void Updater::add_generator(std::shared_ptr<Generator> gen)
{
  generators[gen->get_classname()] = gen;
}

/* ------------------------------------------------------------------ */

const std::vector<std::shared_ptr<Generator>> Updater::get_generators()
{
  std::vector<std::shared_ptr<Generator>> tmp;

  for (const auto &item : generators)
  {
    tmp.push_back(item.second);
  }

  return tmp;
}
