/* ---------------------------------------------------------------------
AddCoMPositions: stands for Adder for Center of Mass added as Positions.

create: 2018/07/13 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_com_positions.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddCoMPositions::AddCoMPositions(ShPtr<GenElement> elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddCoMPositions::compute_with_weights(
  Json &data, ShPtr<GenElement> gen_atoms)
{
  auto id2index_atom = get_map_to_index(gen_atoms->get_data(), "id");

  auto ms_atom = gen_atoms->get_1d_double("mass");
  auto rs_atom = gen_atoms->get_2d_double({"xu", "yu", "zu"});

  for (auto &d : data)
  {
    double m_tmp = 0.0;
    RowArrayXd r_tmp = RowArrayXd::Zero(3);

    int n_atoms = d["atom-ids"].size();

    for (int i = 0; i != n_atoms; ++i)
    {
      int id = d["atom-ids"][i];
      double weight = d["atom-weights"][i];

      int index = id2index_atom[id];
      double mass = ms_atom(index) * weight;

      m_tmp += mass;
      r_tmp += mass * rs_atom.row(index);
    }

    r_tmp /= m_tmp;

    d["mass"] = m_tmp;

    d["xu"] = r_tmp(0);
    d["yu"] = r_tmp(1);
    d["zu"] = r_tmp(2);
  }
}

/* ------------------------------------------------------------------ */

void AddCoMPositions::compute_without_weights(
  Json &data, ShPtr<GenElement> gen_atoms)
{
  auto id2index_atom = get_map_to_index(gen_atoms->get_data(), "id");

  auto ms_atom = gen_atoms->get_1d_double("mass");
  auto rs_atom = gen_atoms->get_2d_double({"xu", "yu", "zu"});

  for (auto &d : data)
  {
    double m_tmp = 0.0;
    RowArrayXd r_tmp = RowArrayXd::Zero(3);

    for (int id : d["atom-ids"])
    {
      int index = id2index_atom[id];
      double mass = ms_atom(index);

      m_tmp += mass;
      r_tmp += mass * rs_atom.row(index);
    }

    r_tmp /= m_tmp;

    d["mass"] = m_tmp;

    d["xu"] = r_tmp(0);
    d["yu"] = r_tmp(1);
    d["zu"] = r_tmp(2);
  }
}

/* ------------------------------------------------------------------ */

void AddCoMPositions::compute_impl(Json &data, Set<Str> &datakeys)
{
  auto gen_atoms = ext_generator->get_element();

  if (!check_containment<Str>(
    gen_atoms->get_keys(), {"id", "mass", "xu", "yu", "zu"}))
  {
    runtime_error(
      "AddCoMPositions needs 'id', 'mass' and '*u' (x/y/z) externally");
    return;
  }

  if (!check_containment<Str>(datakeys, "atom-ids"))
  {
    runtime_error("AddCoMPositions needs 'atom-ids'");
    return;
  }

  if (check_containment<Str>(datakeys, "atom-weights"))
  {
    compute_with_weights(data, gen_atoms);
  }
  else
  {
    compute_without_weights(data, gen_atoms);
  }

  datakeys.insert({"mass", "xu", "yu", "zu"});
}
