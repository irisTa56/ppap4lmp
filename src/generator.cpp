/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "generator.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void Generator::appoint() {

  n_appointment += 1;

}

/* ------------------------------------------------------------------ */

void Generator::cancel() {

  n_appointment -= 1;

}

/* ------------------------------------------------------------------ */

void Generator::goodbye() {

  n_appointment -= 1;

  if (n_appointment == 0) {

    data.clear();

    message(dataname + " has been deleted");
    data_exists = false;

  } else if (n_appointment < 0) {
    runtime_error(dataname + ": Invalid data use is detected");
  }

}

/* ------------------------------------------------------------------ */

void Generator::clockout() {

  if (0 < n_appointment) {
    message("Unused " + std::to_string(n_appointment) + " " + dataname);
  }

}

/* ------------------------------------------------------------------ */

const nlohmann::json &Generator::get_data() {

  check_data();

  return data;

}

/* ------------------------------------------------------------------ */

const pybind11::object Generator::get_data_py() {

  check_data();

  return json2py(data);

}

/* ------------------------------------------------------------------ */

void Generator::check_data() {

  if (!data_exists) {
    this->generate();
    data_exists = true;
  }

}
