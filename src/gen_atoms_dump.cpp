/* ---------------------------------------------------------------------
GenAtomsDump: stands for Generator of Atoms from lammps' Dump file.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <fstream>

#include "gen_atoms_dump.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

GenAtomsDump::GenAtomsDump(
  const std::string &filepath_, int timestep_) : GenAtoms() {

  filepath = filepath_;
  timestep = timestep_;

}

/* ------------------------------------------------------------------ */

GenAtomsDump::GenAtomsDump(
  const std::string &filepath_,
  int timestep_, const std::string &suffix) : GenAtoms(suffix) {

  filepath = filepath_;
  timestep = timestep_;

}

/* ------------------------------------------------------------------ */

void GenAtomsDump::generate() {

  std::ifstream ifs(filepath);
  std::string line;
  bool timestep_matches = false;
  int n_atoms = 0;

  if (!ifs.is_open()) {
    runtime_error("No such a file: " + filepath);
  }

  while (std::getline(ifs, line)) {

    if (line.find("ITEM: TIMESTEP") == 0) {

      std::getline(ifs, line);

      if (std::stoi(line) == timestep) {
        timestep_matches = true;
      }

    } else if (
      line.find("ITEM: NUMBER OF ATOMS") == 0) {

      std::getline(ifs, line);
      n_atoms = std::stoi(line);

    } else if (line.find("ITEM: ATOMS") == 0) {

      if (timestep_matches) {

        auto keys = split(line);
        keys.erase(keys.begin(), keys.begin()+2);

        std::getline(ifs, line);

        auto is_int = get_is_int_vector(line);
        int length = is_int.size();

        for (int i = 0; i < n_atoms; ++i) {

          auto &a = data[i];
          auto strs = split(line);

          for (int j = 0; j < length; ++j) {
            if (is_int[j]) {
              a[keys[j]] = std::stoi(strs[j]);
            } else {
              a[keys[j]] = std::stod(strs[j]);
            }
          }

          std::getline(ifs, line);

        }

        break;

      } else {

        for (int i = 0; i < n_atoms; ++i) {
          std::getline(ifs, line);
        }
      }
    }
  }

}

/* ------------------------------------------------------------------ */

const std::vector<bool> GenAtomsDump::get_is_int_vector(
  const std::string &line) {

  std::vector<bool> is_int;

  auto strs = split(line);

  for (const auto &s : strs) {
    is_int.push_back(s.find(".") == std::string::npos ? true : false);
  }

  return is_int;

}
