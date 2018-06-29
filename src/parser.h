/* ---------------------------------------------------------------------
Parser: is an abstract class to parse data from a file or other
Generators.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PARSER_H
#define PARSER_H

#include "updater.h"

class Parser : public Updater {
 public:
  Parser() = default;
  virtual ~Parser() = default;
  virtual void compute(nlohmann::json &) override;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_parser(py::module &m)
{
  py::class_<Parser,PyUpdater<Parser>,Updater,std::shared_ptr<Parser>>(m, "Parser")
    .def(py::init<>());
}

#endif