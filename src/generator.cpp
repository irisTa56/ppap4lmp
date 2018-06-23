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
    data = nullptr;

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

/* ------------------------------------------------------------------ */

int Generator::count_keys(
  const std::vector<std::string> &keys, bool check_only_front) {

  check_data();

  int count_sum = 0;

  for (const auto &k : keys) {

    if (data.is_array()) {

      if (check_only_front) {

        auto d = data.front();
        int count = d.count(k);

        if (1 < count) {
          message("Duplicate data key: " + k);
        }

        count_sum += count;

      } else {

        int count = 0;

        for (const auto &d : data) {

          int count_tmp = d.count(k);

          if (1 < count_tmp) {
            message("Duplicate data key: " + k);
          }

          count += count_tmp;

        }

        count_sum += count/data.size();

      }

    } else {

      int count = data.count(k);

      if (1 < count) {
        message("Duplicate data key: " + k);
      }

      count_sum += count;

    }
  }

  return count_sum;

}
