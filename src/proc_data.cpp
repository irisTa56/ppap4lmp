/* ---------------------------------------------------------------------
ProcData: stands for Processor which returns Data itself.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "proc_data.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void ProcData::select(pybind11::args args) {

  for (auto a : args) {
    selected_keys.push_back(a.cast<std::string>());
  }

}

/* ------------------------------------------------------------------ */

void ProcData::run_impl(int i_generator) {

  auto &d = generators[i_generator]->get_data();

  if (selected_keys.size() == 0) {

    results[i_generator] = json2py(d);

  } else {

    nlohmann::json j;

    if (d.is_array()) {

      for (const auto &e : d) {

        nlohmann::json k;

        auto end = e.end();

        for (const auto &s : selected_keys) {

          auto val = e.find(s);

          if (val != end) {
            k[s] = *val;
          }
        }

        j.push_back(k);

      }

    } else {

      for (auto s : selected_keys) {
        if (d.count(s)) {
          j[s] = d[s];
        }
      }
    }

    results[i_generator] = json2py(j);

  }

}

/* ------------------------------------------------------------------ */

void ProcData::prepare_impl() {

  results.resize(n_generators);

}

/* ------------------------------------------------------------------ */

const std::vector<pybind11::object> &ProcData::get_results() {

  return results;

}
