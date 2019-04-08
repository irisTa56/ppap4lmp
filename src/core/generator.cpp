/*!
  @file src/core/generator.cpp
  @brief This file has an implementation of the Generator class, which
  is one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/06/21
*/

#include "generator.h"
#include "../core/element.h"
#include "../core/updater.h"

/* ------------------------------------------------------------------ */

void Generator::merge_update_chain(
  const Vec<UpdatePair> &new_chain)
{
  auto &chain = update_chain;

  for (auto it = new_chain.begin(); it != new_chain.end(); ++it)
  {
    if (std::find(chain.begin(), chain.end(), *it) == chain.end())
    {
      bool it_is_inserted = false;

      for (auto jt = chain.begin(); jt != chain.end(); ++jt)
      {
        bool jt_should_be_after_it = false;

        for (auto kt = it+1; kt != new_chain.end(); ++kt)
        {
          if (*kt == *jt)
          {
            jt_should_be_after_it = true;
            break;
          }
        }

        if (jt_should_be_after_it)
        {
          chain.insert(jt, *it);
          it_is_inserted = true;
          break;
        }
      }

      if (!it_is_inserted)
      {
        chain.push_back(*it);
      }
    }
  }
}

/* ------------------------------------------------------------------ */

void Generator::book_to_generate_data()
{
  for (const auto &item : update_chain)
  {
    item.first->increment_bookings();
  }
}

/* ------------------------------------------------------------------ */

void Generator::generate_data()
{
  for (const auto &item : update_chain)
  {
    item.first->update_data(item.second);
  }
}

/* ------------------------------------------------------------------ */

void Generator::finish_using_generated_data()
{
  for (const auto &item : update_chain)
  {
    item.first->decrement_bookings();
  }
}

/* ------------------------------------------------------------------ */

const Vec<UpdatePair> &Generator::get_update_chain()
{
  return update_chain;
}

/* ------------------------------------------------------------------ */
