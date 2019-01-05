/*!
  @file src/processors/pro_radial_distribution_function.h
  @brief This file has a definition of ProRadialDistributionFunction class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef PRO_RADIAL_DISTRIBUTION_FUNCTION_H
#define PRO_RADIAL_DISTRIBUTION_FUNCTION_H

#include <processors/processor.h>

/*!
  @brief ProRadialDistributionFunction computes radial distribution
  function (RDF).

  An object of this class makes a one-dimensional array of
  radial distribution function of particles (can be atoms, beads,
  molecules ...). Each element of the array corresponds to a ratio
  of local density at distance *r* to global density, where *r* is
  distance from a reference particle. The local density at *r* defined
  as a division of the number of particles in a spherical shell
  with radius of *r* by volume of the spherical shell.

  List of radial distribution functions is also computed
  for a multiple snapshots of a simulation.

  Note that a particle which is one of special bonds of
  a reference particle is excluded from a sample used
  for computing radial distribution function. About special bonds,
  please see AddSpecialBonds class.

  About usage in Python,
  please see pybind::py_pro_radial_distribution_function.
*/
class ProRadialDistributionFunction : public Processor {
 protected:
  /*!
    Number of bins in the distance axis.
    The maximum distance in a domain, where the radial distribution
    function is computed, is given as a product of #n_bins
    (if #bin_from_r is `true`) and #bin_width.
  */
  int n_bins = 1;
  /*!
    Width of a bin.
    The maximum distance in a domain, where the radial distribution
    function is computed, is given as a product of #n_bins
    (if #bin_from_r is `true`) and #bin_width.
  */
  double bin_width = 1.0;
  /*!
    If this member is `true`, the bins are <i>[0, dr), [dr, 2*dr),
    ..., [(#n_bins-1)*dr, #n_bins*dr)</i>. If this member is `false`,
    the bins are <i>[0, 0.5*dr), [0.5*dr, 1.5*dr), ...,
    [(#n_bins-1.5)*dr, (#n_bins-0.5)*dr)</i>. Default is `false`.
  */
  bool bin_from_r = false;
  /*!
    If this member is `false` (default), a particle of which distance
    from a reference particle are larger than
    half the simulation box length is excluded from a sample used
    for computing radial distribution function.
    Such particles can be included in the sample for a case of
    small simulation box.
  */
  bool beyond_half = false;
  /*!
    A one-dimensional array of the radial distribution function.
  */
  ArrayXd rdf;
  /*!
    List consisting of temporary radial distribution functions.
    Indices in this list corresponds those in #generators.
  */
  Vec<ArrayXd> rdf_traj;
  /*!
    List consisting of temporary numbers of particles.
    Indices in this list corresponds those in #generators.
  */
  Vec<int> number_traj;
  /*!
    List consisting of temporary volumes of the simulation box.
    Indices in this list corresponds those in #generators.
  */
  Vec<double> volume_traj;
  /*!
    List consisting of temporary numbers of particles
    in a spherical shell with radius of *r*, where *r* is distance
    from a reference particle.
    Indices in this list corresponds those in #generators.
  */
  Vec<ArrayXi> counts_traj;
  /*!
    @copydoc Processor::run_impl

    I am sorry to say that the best documentation for this method
    is its source code...
  */
  virtual void run_impl(
    const int index) override;
 public:
  /*!
    @brief Constructor of ProRadialDistributionFunction class
    for a snapshot of simulation.

    @param targets
    @parblock
      An Element object for particles (can be atoms, beads,
      molecules...).
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `id` : integer
          - `x` : float
          - `y` : float
          - `z` : float
          <span class="remove_in_rdf">
          - `mass` : float <span class="remove_in_table">(for deformation)</span>
          - `I_xx` : float <span class="remove_in_table">(for deformation)</span>
          - `I_yy` : float <span class="remove_in_table">(for deformation)</span>
          - `I_zz` : float <span class="remove_in_table">(for deformation)</span>
          - `I_xy` : float <span class="remove_in_table">(for deformation)</span>
          - `I_xz` : float <span class="remove_in_table">(for deformation)</span>
          - `I_yz` : float <span class="remove_in_table">(for deformation)</span>
          </span>
          - `special-bonds` : array of integers (optional)
        </dd>
      </dl>

    @param box
      An Element object for a simulation box.
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `lo_x` : float
          - `lo_y` : float
          - `lo_z` : float
          - `hi_x` : float
          - `hi_y` : float
          - `hi_z` : float
        </dd>
      </dl>
    @endparblock

    <span class="remove_in_table">
      A GenDict object is constructed taking the `targets` and `box`,
      and then put into #generators by #register_generator.
    </span>
  */
  ProRadialDistributionFunction(
    const ElPtr &targets,
    const ElPtr &box);
  /*!
    @brief Constructor of ProThicknessProfile class
    for multiple snapshots of simulation.

    @param pairs
      List of pairs of two Element objects: the first object is
      for particles and the second object is for a simulation box.
      If each Element object has an array data, all the array should have
      the same length.
      <dl class="property required_ext">
        <dt class="property required_ext">Required property (first)</dt>
        <dd class="property required_ext">
          - `id` : integer
          - `x` : float
          - `y` : float
          - `z` : float
          <span class="remove_in_rdf">
          - `mass` : float <span class="remove_in_table">(for deformation)</span>
          - `I_xx` : float <span class="remove_in_table">(for deformation)</span>
          - `I_yy` : float <span class="remove_in_table">(for deformation)</span>
          - `I_zz` : float <span class="remove_in_table">(for deformation)</span>
          - `I_xy` : float <span class="remove_in_table">(for deformation)</span>
          - `I_xz` : float <span class="remove_in_table">(for deformation)</span>
          - `I_yz` : float <span class="remove_in_table">(for deformation)</span>
          </span>
          - `special-bonds` : array of integers (optional)
        </dd>
      </dl>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property (second)</dt>
        <dd class="property required_ext">
          - `lo_x` : float
          - `lo_y` : float
          - `lo_z` : float
          - `hi_x` : float
          - `hi_y` : float
          - `hi_z` : float
        </dd>
      </dl>

    <span class="remove_in_table">
      GenDict objects are constructed
      taking each element of the `pairs`,
      and then put into #generators by #register_generators.
    </span>
  */
  ProRadialDistributionFunction(
    const Vec<std::pair<ElPtr,ElPtr>> &pairs);
  virtual ~ProRadialDistributionFunction() = default;
  /*!
    @brief Resize #number_traj, #volume_traj and #counts_traj.
    @return None.
  */
  virtual void prepare() override;
  /*!
    @brief Compute #rdf and #rdf_traj from #number_traj, #volume_traj
    and #counts_traj.

    @return None.

    Note that #rdf and an average over elements in #rdf_traj are
    identical only when volume of the simulation box and the number of
    particles are unchanged during the simulation.
  */
  virtual void finish() override;
  /*!
    @brief Set width and number of bins in the distance axis.
    Each bin is a spherical shell of which center is positioned
    at a reference particle.

    @param bin_width_
      Width of a bin.
      <span class="remove_in_table">
        This parameter is assigned to #bin_width.
      </span>

    @param n_bins_
      Number of bins.
      <span class="remove_in_table">
        This parameter is assigned to #n_bins.
      </span>

    @return None.
  */
  void set_bin(
    double bin_width_,
    int n_bins_);
  /*!
    @brief By default, the bins are <i>[0, 0.5*dr), [0.5*dr, 1.5*dr),
    ... </i>. If this method is
    called without a parameter, the bins are set as <i>[0, dr),
    [dr, 2*dr), ... </i>.

    @param bin_from_r_
      A boolean, whether to use bin of which inner radius is *r*
      and outer radius is <i>r+dr</i> (default is `true`).
      <span class="remove_in_table">
        This parameter is assigned to #bin_from_r.
      </span>

    @return None.
  */
  void bin_from_r_to_r_plus_dr(
    bool bin_from_r_ = true);
  /*!
    @brief Use a sample including particles of which distance
    from a reference particle are larger than
    half the simulation box length.

    @param beyond_half_
      A boolean, whether to use particles beyond half the simulation
      box from a reference particle (default is `true`).
      <span class="remove_in_table">
        This parameter is assigned to #beyond_half.
      </span>

    @return None.
  */
  void beyond_half_box_length(
    bool beyond_half_ = true);
  /*!
    @brief Get a one-dimensional array of distance, <i>[0, dr, 2*dr,
    ... ]</i>, where *dr* is width of a bin.

    @return ::ArrayXd (Numpy-Array in Python).
  */
  const ArrayXd get_r_axis();
  /*!
    @brief Get the radial distribution function
    as a one-dimensional array.

    @return #rdf.
  */
  const ArrayXd &get_rdf();
  /*!
    @brief Get a sequence of radial distribution functions
    as list of one-dimensional arrays.

    @return #rdf_traj.
  */
  const Vec<ArrayXd> &get_rdf_traj();
};

#endif
