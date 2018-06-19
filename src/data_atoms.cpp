/* ---------------------------------------------------------------------
This file is for DataAtoms class.

create: 2018/06/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "data_atoms.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

const Eigen::VectorXi &DataAtoms::get_types() {

  return get_iv("types");

}

/* ------------------------------------------------------------------ */

Eigen::ArrayXXd DataAtoms::get_positions(const std::string &type) {

  Eigen::VectorXd x, y, z;

  if (type == "unscaled") {

    if (!is_unscaled()) {

      runtime_error("'unscaled' positions have not been set yet");

    }

    x = get_dv("x");
    y = get_dv("y");
    z = get_dv("z");

  } else if (type == "scaled") {

    if (!is_scaled()) {

      runtime_error("'scaled' positions have not been set yet");

    }

    x = get_dv("xs");
    y = get_dv("ys");
    z = get_dv("zs");

  } else if (type == "unwrapped") {

    if (!is_unwrapped()) {

      runtime_error("'unwrapped' positions have not been set yet");

    }

    x = get_dv("xu");
    y = get_dv("yu");
    z = get_dv("zu");

  } else if (type == "scaled unwrapped") {

    if (!is_scaled_unwrapped()) {

      runtime_error("'scaled unwrapped' positions have not been set yet");

    }

    x = get_dv("xsu");
    y = get_dv("ysu");
    z = get_dv("zsu");

  } else {

    runtime_error("Only 'unscaled', 'scaled', 'unwrapped' and 'scaled unwrapped' are supported");

  }

  Eigen::ArrayXXd r(x.size(), 3);
  r << x, y, z;

  return r;

}

/* ------------------------------------------------------------------ */

bool DataAtoms::is_unscaled() {

  if (has_dv("x") && has_dv("y") && has_dv("z")) {
    return true;
  } else if (!has_dv("x") && !has_dv("y") && !has_dv("z")) {
    return false;
  } else {
    runtime_error("Invalid 'unscaled' positions");
  }

}

/* ------------------------------------------------------------------ */

bool DataAtoms::is_scaled() {

  if (has_dv("xs") && has_dv("ys") && has_dv("zs")) {
    return true;
  } else if (!has_dv("xs") && !has_dv("ys") && !has_dv("zs")) {
    return false;
  } else {
    runtime_error("Invalid 'scaled' positions");
  }

}

/* ------------------------------------------------------------------ */

bool DataAtoms::is_unwrapped() {

  if (has_dv("xu") && has_dv("yu") && has_dv("zu")) {
    return true;
  } else if (!has_dv("xu") && !has_dv("yu") && !has_dv("zu")) {
    return false;
  } else {
    runtime_error("Invalid 'unwrapped' positions");
  }

}

/* ------------------------------------------------------------------ */

bool DataAtoms::is_scaled_unwrapped() {

  if (has_dv("xsu") && has_dv("ysu") && has_dv("zsu")) {
    return true;
  } else if (!has_dv("xsu") && !has_dv("ysu") && !has_dv("zsu")) {
    return false;
  } else {
    runtime_error("Invalid 'scaled unwrapped' positions");
  }

}