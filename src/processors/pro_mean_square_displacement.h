/* ---------------------------------------------------------------------
ProMeanSquareDisplacement: stands for Processor which computes Mean
Square Displacement.

create: 2018/08/26 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_MEAN_SQUARE_DISPLACEMENT_H
#define PRO_MEAN_SQUARE_DISPLACEMENT_H

#include <processors/processor.h>

class ProMeanSquareDisplacement : public Processor {
  bool drift_correction = true;
  List<bool> dimension = {true, true, true};
  ArrayXXd initial_rs;
  List<RowArrayXd> displacement2_traj;
  ArrayXXd displacement2_array;
  ArrayXd mean_square_displacement;
 protected:
  virtual void run_impl(
    int index) override;
 public:
  ProMeanSquareDisplacement(
    List<ShPtr<GenElement>> elems);
  virtual ~ProMeanSquareDisplacement() = default;
  virtual void prepare() override;
  virtual void finish() override;
  void set_dimension(
    bool include_x,
    bool include_y,
    bool include_z);
  void without_drift_correction(
    bool without_drift_correction_ = true);
  const ArrayXXd &get_displacement2_array();
  const ArrayXd &get_mean_square_displacement();
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_pro_mean_square_displacement(py::module &m)
{
  py::class_<ProMeanSquareDisplacement,PyProcessor<ProMeanSquareDisplacement>,Processor,ShPtr<ProMeanSquareDisplacement>>(m, "ProMeanSquareDisplacement")
    .def(py::init<List<ShPtr<GenElement>>>())
    .def("set_dimension", &ProMeanSquareDisplacement::set_dimension)
    .def(
      "without_drift_correction", &ProMeanSquareDisplacement::without_drift_correction,
      py::arg("without_drift_correction_") = false)
    .def(
      "get_displacement2_array", &ProMeanSquareDisplacement::get_displacement2_array,
      py::return_value_policy::reference_internal)
    .def(
      "get_mean_square_displacement", &ProMeanSquareDisplacement::get_mean_square_displacement,
      py::return_value_policy::reference_internal);
}

#endif
