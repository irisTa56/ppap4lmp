/* ---------------------------------------------------------------------
This file is for Generator class.

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
    runtime_error("Invalid data use is detected");
  }

}

/* ------------------------------------------------------------------ */

nlohmann::json &Generator::get_data() {

  check_data();

  return data;

}

/* ------------------------------------------------------------------ */

pybind11::object Generator::get_data_py() {

  check_data();

  return json2py(data);

}

/* ------------------------------------------------------------------ */

void Generator::check_data() {

  if (!data_exists) {
    this->generate();
    data_exists = true;
  }

  if (data.is_array()) {
    filter();
  }

}
