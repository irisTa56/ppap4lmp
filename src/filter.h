/* ---------------------------------------------------------------------
Filter: is an abstract class to filter data.

create: 2018/06/30 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FILTER_H
#define FILTER_H

#include "updater.h"

class Filter : public Updater {
 public:
  Filter() = default;
  Filter(std::shared_ptr<Generator>);
  virtual ~Filter() = default;
  virtual void compute(nlohmann::json &) override;
  virtual const bool is_callable(const std::string &) override;
  virtual const bool is_callable_as_initializer(std::string &) override;
 private:
  bool is_called = false;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_filter(py::module &m)
{
  py::class_<Filter,PyUpdater<Filter>,Updater,std::shared_ptr<Filter>>(m, "Filter")
    .def(py::init<>())
    .def(py::init<std::shared_ptr<Generator>>());
}

#endif