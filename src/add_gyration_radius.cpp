/* ---------------------------------------------------------------------
AddGyrationRadius: stands for Adder for Gyration Radius (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_gyration_radius.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddGyrationRadius::AddGyrationRadius()
{
  callable_datatypes = {"Molecules"};
}

/* ------------------------------------------------------------------ */

void AddGyrationRadius::compute_impl(json &data)
{
  if (!check_key(data, {"mass", "I_xx", "I_yy", "I_zz"}))
  {
    runtime_error(
      "AddGyrationRadius needs the masses and diagonal components of "
      "the inertia moments");
  }

  for (auto &d : data)
  {
    auto reciprocal_mass = 1.0 / double(d["mass"]);

    auto ixx_per_mass = double(d["I_xx"]) * reciprocal_mass;
    auto iyy_per_mass = double(d["I_yy"]) * reciprocal_mass;
    auto izz_per_mass = double(d["I_zz"]) * reciprocal_mass;

    auto tr_per_mass = 0.5 * (ixx_per_mass+iyy_per_mass+izz_per_mass);

    d["Rg"] = sqrt(tr_per_mass);
    d["Rg_x"] = sqrt(ixx_per_mass);
    d["Rg_y"] = sqrt(iyy_per_mass);
    d["Rg_z"] = sqrt(izz_per_mass);
  }
}
