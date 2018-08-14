/* ---------------------------------------------------------------------
Generator: is an abstract class to generate (and manage) data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <algorithm>

#include "generator.h"
#include "utils.h"

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
void Generator::merge_update_chain(const List<UpdatePair> &new_chain)
{
  auto &chain = update_chain;

  for (auto itr = new_chain.begin(); itr != new_chain.end(); ++itr)
  {
    if (std::find(chain.begin(), chain.end(), *itr) == chain.end())
    {
      bool inserted = false;

      for (auto jtr = chain.begin(); jtr != chain.end(); ++jtr)
      {
        bool match = false;

        for (auto ktr = itr+1; ktr != new_chain.end(); ++ktr)
        {
          if (*ktr == *jtr)
          {
            match = true;
            break;
          }
        }

        if (match)
        {
          chain.insert(jtr, *itr);
          inserted = true;
          break;
        }
      }

      if (!inserted)
      {
        chain.push_back(*itr);
      }
    }
  }
}

/* ------------------------------------------------------------------ */

void Generator::appoint()
{
  for (const auto &item : update_chain)
  {
    item.first->increment_remain();
  }
}

/* ------------------------------------------------------------------ */

void Generator::hello()
{
  for (const auto &item : update_chain)
  {
    item.first->update_data(item.second);
  }
}

/* ------------------------------------------------------------------ */

void Generator::goodbye()
{
  for (const auto &item : update_chain)
  {
    item.first->decrement_remain();
  }
}

/* ------------------------------------------------------------------ */

const List<UpdatePair> &Generator::get_update_chain()
{
  return update_chain;
}
