/*!
  @file src/processors/pro_thickness_profile.h
  @brief This file has a definition of ProThicknessProfile class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/07/08
*/

#ifndef PRO_THICKNESS_PROFILE_H
#define PRO_THICKNESS_PROFILE_H

#include <processors/processor.h>

/*!
  @brief ProThicknessProfile computes thickness profile of a film
  consisting of particles (can be atoms, beads, molecules...).

  An object of this class makes list of two-dimensional arrays: each
  array is a two-dimensional profile of film thickness
  for each snapshot of the simulation. Row and column of each array is
  for the *x* and *y* direction, respectively.
  The thickness is measured in the *z* direction.

  Note that each particle is assumed to have a radius,
  and an excluded volume defined by the radius.
  Film thickness at point of <i>(x, y)</i> is defined as the highest
  *z* coordinate inside excluded volume of any of the particles.

  About usage in Python,
  please see pybind::py_pro_thickness_profile.
*/
class ProThicknessProfile : public Processor {
  /*!
    The number of grids in *x* direction.
  */
  int nx = 1;
  /*!
    The number of grids in *y* direction.
  */
  int ny = 1;
  /*!
    Whether to shift grids at which film thickness is computed.
    If this member is `false`, grids in the *x* direction are set as
    <i>x_0, x_0+dx, x_0+2*dx, ..., x_0+(#nx-1)*dx</i>,
    where *x_0* is the minimum *x* coordinate in the simulation box
    and *dx* is the grid width.
    If this member is `true`, grids in the *x* direction are set as
    <i>x_0+0.5*dx, x_0+1.5*dx, x_0+2.5*dx, ..., x_0+(#nx-0.5)*dx</i>.
    Default is `false`.
  */
  bool shift_half = false;
  /*!
    Calculate film thickness after subtracting a value of this member
    from *z* coordinate of the particles. Default is 0.
  */
  double offset = 0.0;
  /*!
    Computation conditions (origin of computed area, grid width
    and the number of grads) used by this object are stored here.
    If the simulation box is unchanged during the simulation,
    every element of this member is identical.
  */
  Vec<Json> conditions;
  /*!
    Time series (if a simulation trajectory is used as an input) of
    two-dimensional profile of film thickness. Indices in this list
    corresponds those in #generators.
  */
  Vec<ArrayXXd> profiles;
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
    @brief Constructor of ProThicknessProfile class
    for a snapshot of simulation.

    @param atoms
    @parblock
      An Element object for particles (can be atoms, beads,
      molecules...) forming a film.
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `x` : float
          - `y` : float
          - `z` : float
          - `radius` : float
        </dd>
      </dl>

    @param box
      An Element object for a simulation box.
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `lo_x` : float
          - `lo_y` : float
          - `hi_x` : float
          - `hi_y` : float
        </dd>
      </dl>
    @endparblock

    <span class="remove_in_table">
      A GenDict object is constructed taking the `atoms` and `box`,
      and then put into #generators by #register_generator.
    </span>
  */
  ProThicknessProfile(
    const ElPtr &atoms,
    const ElPtr &box);
  /*!
    @brief Constructor of ProThicknessProfile class
    for multiple snapshots of simulation.

    @param pairs
      List of pairs of two Element objects: the first object is
      for particles forming a film and the second object is
      for a simulation box.
      If each Element object has an array data, all the array should have
      the same length.
      <dl class="property required_ext">
        <dt class="property required_ext">Required property (first)</dt>
        <dd class="property required_ext">
          - `x` : float
          - `y` : float
          - `z` : float
          - `radius` : float
        </dd>
      </dl>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property (second)</dt>
        <dd class="property required_ext">
          - `lo_x` : float
          - `lo_y` : float
          - `hi_x` : float
          - `hi_y` : float
        </dd>
      </dl>

    <span class="remove_in_table">
      GenDict objects are constructed
      taking each element of the `pairs`,
      and then put into #generators by #register_generators.
    </span>
  */
  ProThicknessProfile(
    const Vec<std::pair<ElPtr,ElPtr>> &pairs);
  virtual ~ProThicknessProfile() = default;
  /*!
    @brief Resize #conditions and #profiles.
    @return None.
  */
  virtual void prepare() override;
  /*!
    @brief Specify the number of grids in the *x* and *y* directions.

    @param nx_
      The number of grids in the *x* direction.
      <span class="remove_in_table">
        This parameter is assigned to #nx.
      </span>

    @param ny_
      The number of grids in the *y* direction.
      <span class="remove_in_table">
        This parameter is assigned to #ny.
      </span>

    @return None.
  */
  void set_grid(
    int nx_,
    int ny_);
  /*!
    @brief Specify the offset for thickness (height).

    @param offset_
      Film thickness is calculated after subtracting this value
      from *z* coordinate of particles.
      <span class="remove_in_table">
        This parameter is assigned to #offset.
      </span>

    @return None.
  */
  void set_offset(
    double offset_);
  /*!
    @brief Increment coordinates of the grid points by half
    the grid width. By default, grids in the *x* direction are
    set as <i>x_0, x_0+dx, x_0+2*dx, ... </i>, where *x_0* is
    the minimum *x* coordinate in the simulation box and *dx* is
    the grid width. If this method is called without a parameter,
    the grids are set as <i>x_0+0.5*dx, x_0+1.5*dx, x_0+2.5*dx,
    ... </i>.

    @param shift_half_
      A boolean, whether to shift the grid points or not
      (default is `true`).
      <span class="remove_in_table">
        This parameter is assigned to #shift_half.
      </span>

    @return None.
  */
  void shift_half_delta(
    bool shift_half_ = true);
  /*!
    @brief Get computation conditions (origin of computed area,
    grid width and the number of grads) used by this object
    as list of dictionary.

    @return #conditions.
  */
  const Vec<Json> &get_conditions();
  /*!
    @brief Get a sequence of two-dimensional profile of film thickness
    as list of two-dimensional arrays. Row and column of each array is
    for the *x* and *y* direction, respectively.

    @return #profiles.
  */
  const Vec<ArrayXXd> &get_profiles();
};

#endif
