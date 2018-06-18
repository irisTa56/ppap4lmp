/* ---------------------------------------------------------------------
This file is for ExtrBoxDump class.

create: 2018/06/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <fstream>

#include "extr_box_dump.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

ExtrBoxDump::ExtrBoxDump(const std::string &filepath_, int timestep_) {

  filepath = filepath_;
  timestep = timestep_;

}

/* ------------------------------------------------------------------ */

void ExtrBoxDump::extract() {

  std::ifstream ifs(filepath);
  std::string line;
  bool is_now = false;
  int n_skip = 0;

  if (!ifs.is_open()) {
    runtime_error("No such a file " + filepath);
  }

  while (std::getline(ifs,line)) {

    if (line.find("ITEM: TIMESTEP") == 0) {

      std::getline(ifs,line);
      if (std::stoi(line) == timestep) {
        is_now = true;
        n_skip = 0;
      }

    } else if (line.find("ITEM: NUMBER OF ATOMS") == 0 && !is_now) {

      std::getline(ifs,line);
      n_skip = std::stoi(line);

    } else if (line.find("ITEM: BOX BOUNDS") == 0 && is_now) {

      std::vector<std::string> strs = split(line);
      Eigen::VectorXi periodicity = Eigen::VectorXi::Zero(3);

      for (int i = 0; i < 3; ++i) {

        if (strs[i+3] == "pp") {
          periodicity(i) = 1;
        }

      }

      data->set_periodicity(periodicity);

      Eigen::ArrayXXd edge = Eigen::ArrayXXd::Zero(3, 2);

      for (int i = 0; i < 3; ++i) {

        std::getline(ifs,line);

        std::vector<std::string> strs = split(line);

        edge(i,0) = std::stod(strs[0]);
        edge(i,1) = std::stod(strs[1]);

      }

      data->set_edge(edge);

      break;

    } else if (line.find("ITEM: ATOMS") == 0) {

      for (int i = 0; i < n_skip; ++i) {
        std::getline(ifs,line);
      }

    }

  }

}
