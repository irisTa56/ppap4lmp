/* ---------------------------------------------------------------------
GenList: stands for Generator List containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_LIST_H
#define GEN_LIST_H

#include "generator.h"

class GenList : public Generator {
  std::vector<std::shared_ptr<Generator>> generator_list;
 public:
  GenList(std::vector<std::shared_ptr<Generator>>);
  virtual ~GenList() = default;
  virtual const json &get_data() override;
  virtual std::shared_ptr<Generator> get_generator(int) override;
  using Generator::get_generator;
  const int get_length();
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_gen_list(py::module &m)
{
  py::class_<GenList,PyGenerator<GenList>,Generator,std::shared_ptr<GenList>>(m, "GenList")
    .def(py::init<std::vector<std::shared_ptr<Generator>>>())
    .def("get_length", &GenList::get_length);
}

#endif
