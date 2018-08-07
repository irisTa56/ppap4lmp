/* ---------------------------------------------------------------------
AddCoMPosition: stands for Adder for Center of Mass added as Position.

create: 2018/07/13 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_com_position.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddCoMPosition::AddCoMPosition(std::shared_ptr<Generator> gen)
{
  check_reference_generator(gen, "Atoms");
  callable_datatypes = {"Molecules"};
}

/* ------------------------------------------------------------------ */

void AddCoMPosition::compute_impl(json &data)
{
  auto &atoms = reference_generator->get_data();

  if (!check_key(atoms, {"id", "mass", "xu", "yu", "zu"}))
  {
    runtime_error(
      "AddCoMPosition needs IDs, masses and unwrapped "
      "positions of Atoms");
  }

  auto atom_id2index = get_map_to_index(atoms, "id");

  auto atom_ms = reference_generator->get_1d_double("mass");
  auto atom_rs = reference_generator->get_2d_double({"xu", "yu", "zu"});

  for (auto &d : data)
  {
    double m_tmp = 0.0;
    RowArrayXd r_tmp = RowArrayXd::Zero(3);

    for (int id : d["atom-ids"])
    {
      int index = atom_id2index[id];
      double mass = atom_ms(index);

      m_tmp += mass;
      r_tmp += mass * atom_rs.row(index);
    }

    r_tmp /= m_tmp;

    d["mass"] = m_tmp;

    d["xu"] = r_tmp(0);
    d["yu"] = r_tmp(1);
    d["zu"] = r_tmp(2);
  }
}
