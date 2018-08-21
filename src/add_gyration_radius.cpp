/* ---------------------------------------------------------------------
AddGyrationRadius: stands for Adder for Gyration Radius (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_gyration_radius.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void AddGyrationRadius::compute_impl(
  Json &data,
  Set<Str> &datakeys)
{
  check_keys(datakeys, {"mass", "I_xx", "I_yy", "I_zz"});

  for (auto &d : data)
  {
    auto reciprocal_mass = 1.0 / d["mass"].get<double>();

    auto ixx_per_mass = d["I_xx"].get<double>() * reciprocal_mass;
    auto iyy_per_mass = d["I_yy"].get<double>() * reciprocal_mass;
    auto izz_per_mass = d["I_zz"].get<double>() * reciprocal_mass;

    auto tr_per_mass = 0.5 * (ixx_per_mass+iyy_per_mass+izz_per_mass);

    d["Rg"] = sqrt(tr_per_mass);
    d["Rg_x"] = sqrt(ixx_per_mass);
    d["Rg_y"] = sqrt(iyy_per_mass);
    d["Rg_z"] = sqrt(izz_per_mass);
  }

  datakeys.insert({"Rg", "Rg_x", "Rg_y", "Rg_z"});
}
