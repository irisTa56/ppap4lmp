/* ---------------------------------------------------------------------
AddRename: stands for Adder to create new property by Renaming existing
property.

create: 2018/08/17 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_rename.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddRename::AddRename(const Str &key_old_, const Str &key_new_)
{
  key_old = key_old_;
  key_new = key_new_;
}

/* ------------------------------------------------------------------ */

void AddRename::compute_impl(Json &data, Set<Str> &datakeys)
{
  if (!check_containment<Str>(datakeys, key_old))
  {
    runtime_error("AddRename needs '" + key_old + "'");
    return;
  }

  if (check_containment<Str>(datakeys, key_new) && !do_overwrite)
  {
    runtime_error("AddRename cannot overwrite '" + key_new + "'");
    return;
  }

  if (data.is_array())
  {
    for (auto &d : data)
    {
      auto itr = d.find(key_old);
      d[key_new] = *itr;
      d.erase(itr);
    }
  }
  else
  {
    auto itr = data.find(key_old);
    data[key_new] = *itr;
    data.erase(itr);
  }

  datakeys.erase(key_old);
  datakeys.insert(key_new);
}

/* ------------------------------------------------------------------ */

ShPtr<AddRename> AddRename::overwrite(bool do_overwrite_)
{
  do_overwrite = do_overwrite_;

  return shared_from_this();
}
