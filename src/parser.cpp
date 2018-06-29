/* ---------------------------------------------------------------------
Parser: is an abstract class to parse data from a file or other
Generators.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "parser.h"

/* ------------------------------------------------------------------ */

void Parser::preprocess()
{
  for (const auto &item : dict_gen)
  {
    item.second->appoint();
  }
}

/* ------------------------------------------------------------------ */

void Parser::postprocess()
{
  for (const auto &item : dict_gen)
  {
    item.second->goodbye();
  }
}

/* ------------------------------------------------------------------ */

void Parser::add_generators(std::shared_ptr<Generator> gen)
{
  dict_gen[gen->get_classname()] = gen;
}