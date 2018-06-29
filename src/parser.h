/* ---------------------------------------------------------------------
Parser: is an abstract class to parse data from a file or other
Generators.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PARSER_H
#define PARSER_H

#include "generator.h"

class Parser {
 public:
  Parser() = default;
  virtual ~Parser() = default;
  virtual void compute(nlohmann::json &data) = 0;
  void preprocess();
  void postprocess();
  void add_generators(std::shared_ptr<Generator>);
 protected:
  std::unordered_map<std::string,std::shared_ptr<Generator>> dict_gen;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class PAR = Parser>
class PyParser : public PAR {
 public:
  using PAR::PAR;
  void compute(nlohmann::json &data) override
  {
    PYBIND11_OVERLOAD_PURE(void, PAR, compute, data);
  }
};

static void pybind_parser(py::module &m)
{
  py::class_<Parser,PyParser<>,std::shared_ptr<Parser>>(m, "Parser")
    .def(py::init<>());
}

#endif