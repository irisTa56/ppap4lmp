/*!
  @file src/processors/pro_radial_distribution_function_with_deformation.h
  @brief This file has a definition of ProRadialDistributionFunctionWithDeformation class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H
#define PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H

#include <processors/pro_radial_distribution_function.h>

//! \e ProRDF is an alias for ProRadialDistributionFunction class.
using ProRDF = ProRadialDistributionFunction;

/*!
  @brief ProRadialDistributionFunctionWithDeformation computes
  radial distribution function (RDF) taking deformation of particles
  into consideration.

  Deformation is guessed using gyration radius in
  perpendicular and parallel directions of the point-to-point vector.

  An object of this class makes a one-dimensional array of
  radial distribution function with deformation of volumetric particles
  such as beads and molecules.
  This type of radial distribution function is different
  from original radial distribution function in terms of distance
  between two particles. The distance is modified taking deformation of
  the particles into consideration. Deformation of the particle is
  estimated using gyration radius in a parallel direction of
  the particle-to-particle vector. This gyration radius can be computed
  by subtracting gyration radius \e around the particle-to-particle
  axis from general gyration radius.
  Difference between the gyration radius \e in the particle-to-particle
  axis and the general gyration radius is added to the distance.

  The above mentioned three types of gyration radius, that is,
  general gyration radius, gyration radius
  \e around the particle-to-particle axis, and gyration radius
  \e in the particle-to-particle vector are also stored as functions of
  distance \e r, where \e r is distance from a reference particle
  \e without modification.

  List of radial distribution functions and lists of functions
  for three types of gyration radius are also computed
  for a multiple snapshots of a simulation.

  Note that a particle which is one of special bonds of
  a reference particle is excluded from a sample used
  for computing radial distribution function. About special bonds,
  please see AddSpecialBonds class.

  About usage in Python,
  please see pybind::py_pro_radial_distribution_function_with_deformation.
*/
class ProRadialDistributionFunctionWithDeformation : public ProRDF {
  /*!
    Since distance between particles can be changed by modification,
    particles of which original distances from a reference particle are
    larger than the maximum distance in a domain,
    where the radial distribution function is computed,
    might be counted. This program uses a sample including particles
    up to the maximum distance \e plus this member.
  */
  double margin = 1.0;
  /*!
    Averaged square of general gyration radius as a function
    of distance from a reference particle.
  */
  ArrayXd Rg2_array;
  /*!
    Averaged square of gyration radius
    \e in the particle-to-particle axis
    as a function of distance from a reference particle.
  */
  ArrayXd Rg2_para_array;  // parallel
  /*!
    Averaged square of gyration radius
    \e around the particle-to-particle axis
    as a function of distance from a reference particle.
  */
  ArrayXd Rg2_perp_array;  // perpendicular
  /*!
    List consisting of temporary averaged square
    of general gyration radius as a function of distance
    from a reference particle.
    Indices in this list corresponds those in #generators.
  */
  Vec<ArrayXd> Rg2_array_traj;
  /*!
    List consisting of temporary averaged square of gyration radius
    \e in the particle-to-particle axis
    as a function of distance from a reference particle.
    Indices in this list corresponds those in #generators.
  */
  Vec<ArrayXd> Rg2_para_array_traj;
  /*!
    List consisting of temporary averaged square of gyration radius
    \e around the particle-to-particle axis
    as a function of distance from a reference particle.
    Indices in this list corresponds those in #generators.
  */
  Vec<ArrayXd> Rg2_perp_array_traj;
  /*!
    List consisting of temporary numbers of particles
    in a spherical shell with radius of \e r, where \e r is distance
    from a reference particle \e without modification.
    Indices in this list corresponds those in #generators.
  */
  Vec<ArrayXi> raw_counts_traj;
  /*!
    List consisting of temporary sum of square
    of general gyration radius as a function of distance
    from a reference particle.
    Indices in this list corresponds those in #generators.
  */
  Vec<ArrayXd> Rg2_sum_traj;
  /*!
    List consisting of temporary sum of square of gyration radius
    \e in the particle-to-particle axis
    as a function of distance from a reference particle.
    Indices in this list corresponds those in #generators.
  */
  Vec<ArrayXd> Rg2_para_sum_traj;
  /*!
    List consisting of temporary sum of square of gyration radius
    \e around the particle-to-particle axis
    as a function of distance from a reference particle.
    Indices in this list corresponds those in #generators.
  */
  Vec<ArrayXd> Rg2_perp_sum_traj;
 protected:
  /*!
    @copydoc Processor::run_impl

    I am sorry to say that the best documentation for this method
    is its source code...
  */
  virtual void run_impl(
    const int index) override;
 public:
  using ProRDF::ProRDF;
  virtual ~ProRadialDistributionFunctionWithDeformation() = default;
  /*!
    @brief Call ProRDF::prepare and then resize #raw_counts_traj,
    #Rg2_sum_traj, #Rg2_para_sum_traj and #Rg2_perp_sum_traj.
    @return None.
  */
  virtual void prepare() override;
  /*!
    @brief Call ProRDF::finish and then compute #Rg2_array,
    #Rg2_para_array, #Rg2_perp_array, #Rg2_array_traj,
    #Rg2_para_array_traj and #Rg2_perp_array_traj
    from #raw_counts_traj, #Rg2_sum_traj, #Rg2_para_sum_traj
    and #Rg2_perp_sum_traj.

    @return None.

    Note that #Rg2_array (#Rg2_para_array/#Rg2_perp_array) and
    an average over elements in #Rg2_array_traj
    (#Rg2_para_array/#Rg2_perp_array_traj) are identical
    only when volume of the simulation box and the number of
    particles are unchanged during the simulation.
  */
  virtual void finish() override;
  /*!
    @brief Set margin for distance from a reference particle:
    this program uses a sample including particles of which distance
    from a reference particle are less than the maximum distance
    in a domain, where the radial distribution function is computed,
    \e plus the margin.

    @param margin_
      Consider particles up to the maximum distance in the domain
      \e plus this value.
      <span class="remove_in_table">
        This parameter is assigned to #margin.
      </span>

    @return None.
  */
  void set_margin(
    double margin_);
  /*!
    @brief Get averaged gyration radius as function of distance
    from a reference particle. The returned value is dictionary
    of which keys are \c isotropic, \c parallel and \c perpendicular,
    and corresponding values are functions for general gyration radius,
    gyration radius \e in the particle-to-particle axis
    and gyration radius \e around the particle-to-particle axis,
    respectively.

    @return Dictionary consisting of square rooted #Rg2_array,
    #Rg2_para_array and #Rg2_perp_array.
  */
  Map<Str,ArrayXd> get_gyration_radius();
  /*!
    @brief Get list of temporary gyration radius as function
    of distance from a reference particle. The returned value is
    dictionary of which keys are \c isotropic, \c parallel
    and \c perpendicular, and corresponding values are lists
    of functions for general gyration radius, gyration radius
    \e in the particle-to-particle axis and gyration radius
    \e around the particle-to-particle axis, respectively.
    Each element of the lists corresponds to each snapshot
    of the simulation.

    @return Dictionary consisting of list created by square rooting
    each element of #Rg2_array_traj, #Rg2_para_array_traj
    and #Rg2_perp_array_traj.
  */
  Map<Str,Vec<ArrayXd>> get_gyration_radius_traj();
  /*!
    @brief Get averaged square of gyration radius as function
    of distance from a reference particle. The returned value is
    dictionary of which keys are \c isotropic, \c parallel
    and \c perpendicular, and corresponding values are function for
    general gyration radius, gyration radius
    \e in the particle-to-particle axis and gyration radius
    \e around the particle-to-particle axis, respectively.

    @return Dictionary consisting of #Rg2_array, #Rg2_para_array
    and #Rg2_perp_array.
  */
  Map<Str,ArrayXd> get_squared_gyration_radius();
  /*!
    @brief Get list of temporary square of gyration radius as function
    of distance from a reference particle. The returned value is
    dictionary of which keys are \c isotropic, \c parallel
    and \c perpendicular, and corresponding values are lists
    of functions for general gyration radius, gyration radius
    \e in the particle-to-particle axis and gyration radius
    \e around the particle-to-particle axis, respectively.
    Each element of the lists corresponds to each snapshot
    of the simulation.

    @return Dictionary consisting of #Rg2_array_traj,
    #Rg2_para_array_traj and #Rg2_perp_array_traj.
  */
  Map<Str,Vec<ArrayXd>> get_squared_gyration_radius_traj();
};

/*!
  @brief \e ProRDFWD is an alias
  for ProRadialDistributionFunctionWithDeformation class.
*/
using ProRDFWD = ProRadialDistributionFunctionWithDeformation;

#endif