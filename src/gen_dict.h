/* ---------------------------------------------------------------------
GenDict: stands for Generator Dictionary containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_DICT_H
#define GEN_DICT_H

#include "generator.h"

class GenDict : public Generator {
  std::unordered_map<std::string,std::shared_ptr<Generator>> generator_dict;
 public:
  GenDict(std::unordered_set<std::shared_ptr<Generator>>);
  virtual ~GenDict() = default;
  virtual const json &get_data() override;
  virtual std::shared_ptr<Generator> get_generator(
    const std::string &) override;
  using Generator::get_generator;
  const std::unordered_set<std::string> get_keys();
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_gen_dict(py::module &m)
{
  py::class_<GenDict,PyGenerator<GenDict>,Generator,std::shared_ptr<GenDict>>(m, "GenDict")
    .def(py::init<std::unordered_set<std::shared_ptr<Generator>>>())
    .def("get_keys", &GenDict::get_keys);
}

#endif
