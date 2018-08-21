/* ---------------------------------------------------------------------
Generator: is an abstract class to generate (and manage) data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "generator.h"
#include "utils.h"

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
void Generator::merge_update_chain(
  const List<UpdatePair> &new_chain)
{
  auto &chain = update_chain;

  for (auto it = new_chain.begin(); it != new_chain.end(); ++it)
  {
    if (std::find(chain.begin(), chain.end(), *it) == chain.end())
    {
      bool inserted = false;

      for (auto jt = chain.begin(); jt != chain.end(); ++jt)
      {
        bool match = false;

        for (auto kt = it+1; kt != new_chain.end(); ++kt)
        {
          if (*kt == *jt)
          {
            match = true;
            break;
          }
        }

        if (match)
        {
          chain.insert(jt, *it);
          inserted = true;
          break;
        }
      }

      if (!inserted)
      {
        chain.push_back(*it);
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
