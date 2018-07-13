/* ---------------------------------------------------------------------
AddCoMPosition: stands for Adder for Center of Mass added as Position.

create: 2018/07/13 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_com_position.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddCoMPosition::AddCoMPosition(
  std::shared_ptr<Generator> gen)
{
  if (gen->get_datatype() == "Atoms")
  {
    reference_generator = gen;
  }
  else
  {
    runtime_error(
      "AddCoMPosition cannot use " + gen->get_dataname());
  }

  callable_datatypes = {"Molecules"};
}

/* ------------------------------------------------------------------ */

void AddCoMPosition::compute_impl(json &data)
{
  if (!check_key(data, "atom-ids"))
  {
    runtime_error("Atoms-IDs do not exist");
  }

  auto atom_ms = reference_generator->get_1d_double("mass");
  auto atom_rs = reference_generator->get_2d_double({"xu", "yu", "zu"});

  auto atom_id2index = get_map_to_index(
    reference_generator->get_data(), "id");

  for (auto &d : data)
  {
    double m_tmp = 0.0;
    Eigen::Array3d r_tmp = Eigen::ArrayXd::Zero(3);

    for (int id : d["atom-ids"])
    {
      auto index = atom_id2index[id];
      auto mass = atom_ms(index);

      m_tmp += mass;
      r_tmp += mass * atom_rs.row(index);
    }

    r_tmp /= m_tmp;

    d["xu"] = r_tmp(0);
    d["yu"] = r_tmp(1);
    d["zu"] = r_tmp(2);

    d["mass"] = m_tmp;
  }
}
