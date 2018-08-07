/* ---------------------------------------------------------------------
GenList: stands for Generator List containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "gen_list.h"
#include "utils.h"

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
GenList::GenList(std::vector<std::shared_ptr<Generator>> generator_list_)
{
  generator_list = generator_list_;

  auto subtype = generator_list.front()->get_datatype();

  for (auto gen : generator_list)
  {
    if (subtype != gen->get_datatype())
    {
      runtime_error("GenList must contain the same type elements");
    }
  }

  datatype = "List(" + subtype + ")";

  instance_count++;
  dataname = datatype + "_" + std::to_string(instance_count);

  for (auto gen : generator_list)
  {
    merge_update_chain(gen->get_update_chain());
  }
}

/* ------------------------------------------------------------------ */

const json &GenList::get_data()
{
  message("You got data from GenList, " + dataname);
  return data;
}

/* ------------------------------------------------------------------ */

std::shared_ptr<Generator> GenList::get_generator(int index)
{
  return generator_list[index];
}

/* ------------------------------------------------------------------ */

const int GenList::get_length()
{
  return generator_list.size();
}