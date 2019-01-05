/*!
  @file src/processors/pro_mean_square_displacement.h
  @brief This file has a definition of ProMeanSquareDisplacement class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/08/26
*/

#ifndef PRO_MEAN_SQUARE_DISPLACEMENT_H
#define PRO_MEAN_SQUARE_DISPLACEMENT_H

#include <processors/processor.h>

/*!
  @brief ProMeanSquareDisplacement computes mean square displacement
  (MSD).

  An object of this class makes a two-dimensional array
  of squared displacements from initial position for each target
  (can be an atom, bead, molecule...) over a simulation trajectory.
  Each row of the array corresponds to each snapshot of a simulation,
  and each column of the array corresponds to each target.
  By averaging over columns of the array, the object of this class
  also makes a one-dimensional array for the mean square displacement.

  About usage in Python,
  please see pybind::py_pro_mean_square_displacement.
*/
class ProMeanSquareDisplacement : public Processor {
  /*!
    Whether to correct a drift of center of mass
    of the simulation system (default is `true`).
    If the initial structure of the simulation has some biases
    of position or velocity, drift of the simulation system
    (translational displacement of center of mass of the system)
    can occur and, as the result, distort the mean square displacement.
  */
  bool drift_correction = true;
  /*!
    Dimensions to be considered in computing squared displacements.
    Three elements of this member corresponds to *x*, *y*,
    and *z* direction, respectively. Only if an element of this member
    is `true`, displacement in the corresponding direction is added to
    resulted displacement. Default is `true` for all the direction.
  */
  Vec<bool> dimension = {true, true, true};
  /*!
    Initial positions of targets. The first element of #generators is
    used for the initial positions.
  */
  ArrayXXd initial_rs;
  /*!
    List in which ::RowArrayXd objects of computed squared
    displacements of each target are stored.
    Indices in this list corresponds those in #generators.
  */
  Vec<RowArrayXd> displacement2_traj;
  /*!
    A two-dimensional array of squared displacements
    from initial position for each target over a simulation trajectory.
    Each column corresponds to time series of the squared displacement
    for each target, and each row corresponds to each element
    of #generators (snapshot of simulation).
  */
  ArrayXXd displacement2_array;
  /*!
    The mean square displacement.
    Each element corresponds to each element of #generators
    (snapshot of simulation).
  */
  ArrayXd mean_square_displacement;
 protected:
  /*!
    @copydoc Processor::run_impl

    I am sorry to say that the best documentation for this method
    is its source code...
  */
  virtual void run_impl(
    const int index) override;
 public:
  /*!
    @brief Constructor of ProMeanSquareDisplacement class.

    @param elems
      List of Element objects for atoms, beads, molecules...
      If each Element object has an array data, all the array should have
      the same length.
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `id` : integer
          - `xu` : float
          - `yu` : float
          - `zu` : float
          - `mass` : float (for drift correction)
        </dd>
      </dl>

    <span class="remove_in_table">
      Element objects in the `elems` are put into #generators
      by #register_generators.
    </span>
  */
  ProMeanSquareDisplacement(
    const Vec<ElPtr> &elems);
  virtual ~ProMeanSquareDisplacement() = default;
  /*!
    @brief Set initial positions and resize #displacement2_traj.
    @return None.
  */
  virtual void prepare() override;
  /*!
    @brief Fill #displacement2_array with values
    of #displacement2_traj, and calculate #mean_square_displacement
    by averaging over columns of #displacement2_array.

    @return None.

    Each row of #displacement2_array corresponds to
    each element of #displacement2_traj.
  */
  virtual void finish() override;
  /*!
    @brief Specify dimensions to be considered. By default,
    the mean square displacement is computed in three dimensions.
    To compute the mean square displacement in *xy* place, for example,
    the third parameter of this method must be set to `false`.

    @param include_x
      A boolean, whether component in the *x* direction is included in
      squared displacement.
      <span class="remove_in_table">
        This parameter is stored as the first element of #dimension.
      </span>

    @param include_y
      A boolean, whether component in the *y* direction is included in
      squared displacement.
      <span class="remove_in_table">
        This parameter is stored as the second element of #dimension.
      </span>

    @param include_z
      A boolean, whether component in the *z* direction is included in
      squared displacement.
      <span class="remove_in_table">
        This parameter is stored as the third element of #dimension.
      </span>

    @return None.
  */
  void set_dimension(
    bool include_x,
    bool include_y,
    bool include_z);
  /*!
    @brief Disable to correct a drift of center of mass
    of the simulation system.

    @param without_drift_correction_
      Whether disable the drift correction or not (default is `true`).
      <span class="remove_in_table">
        Negation of this parameter is assigned to #drift_correction.
      </span>

    @return None.
  */
  void without_drift_correction(
    bool without_drift_correction_ = true);
  /*!
    @brief Get computed time series of squared displacements
    from initial position for each target as a two-dimensional array:
    each row corresponds to each snapshot of the simulation
    and each column corresponds to each target.

    @return #displacement2_array.
  */
  const ArrayXXd &get_displacement2_array();
  /*!
    @brief Get time series of the mean square displacement
    as a one-dimensional array. Each element of the array corresponds
    to each snapshot of the simulation.

    @return #mean_square_displacement.
  */
  const ArrayXd &get_mean_square_displacement();
};

#endif
