/*!
  @file src/processors/pro_time_correlation_in_molecule.h
  @brief This file has a definition of ProTimeCorrelationInMolecule class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/10/24
*/

#ifndef PRO_TIME_CORRELATION_IN_MOLECULE_H
#define PRO_TIME_CORRELATION_IN_MOLECULE_H

#include <processors/processor.h>

/*!
  @brief ProTimeCorrelationInMolecule computes
  time correlation function of atom-to-atom vector in each molecule.

  An object of this class makes a two-dimensional array
  of time correlation coefficients of vectors between two atoms
  belonging to the same molecule.
  Each row of the array corresponds to each snapshot of a simulation,
  and each column of the array corresponds to each molecule.
  In other words, each column is a time correlation function
  of atom-to-atom vector in each molecule.

  About usage in Python,
  please see pybind::py_pro_time_correlation_in_molecule.
*/
class ProTimeCorrelationInMolecule : public Processor {
  /*!
    Zero-based index for an atom in a molecule.
    Time correlation function of a vector between two atoms
    specified by #index1_in_mol and #index2_in_mol is calculated
    for each molecule.
  */
  int index1_in_mol = 0;
  /*!
    Zero-based index for an atom in a molecule.
    Time correlation function of a vector between two atoms
    specified by #index1_in_mol and #index2_in_mol is calculated
    for each molecule.
  */
  int index2_in_mol = 0;
  /*!
    Only molecules whose type is #target_moltype are analyzed
    (default is 1). Note that if molecules do not have `type` property,
    1 is used as their types.
  */
  int target_moltype = 1;
  /*!
    Initial vectors connecting specified two atoms in the same molecule.
    The first element of #generators is used for the initial positions.
  */
  Vec<RowVector3d> initial_vectors;
  /*!
    Reciprocals of squared norms of #initial_vectors.
  */
  Vec<double> initial_reciprocal_norm2;
  /*!
    List in which ::RowArrayXd objects of computed time correlation
    coefficients for each molecule are stored.
    Indices in this list corresponds those in #generators.
  */
  Vec<RowArrayXd> coefficients_traj;
  /*!
    A two-dimensional array of computed time correlation coefficients.
    Each column corresponds to a time correlation function
    for each molecule, and each row corresponds to each element
    of #generators (snapshot of simulation).
  */
  ArrayXXd coefficients_array;
  /*!
    An *averaged* time correlation function.
    Each element corresponds to each element of #generators
    (snapshot of simulation).
  */
  ArrayXd time_correlation_function;
  /*
    @brief Compute intramolecular vectors
    and conduct customized manipulation using them.

    @param callback
      Define a customized manipulation using intramolecular vectors.

    @param el_mols
      An Element object containing molecule data.

    @param el_atoms
      An Element object containing atom data.

    @return None.
  */
  void compute_temporary_vectors(
    std::function<void(const RowVector3d &)> callback,
    const ElPtr &el_mols,
    const ElPtr &el_atoms);
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
    @brief Constructor of ProTimeCorrelationInMolecule class.

    @param pairs
      List of pairs of two Element objects: the first object is
      for molecules and the second object is for atoms.
      If each Element object has an array data, all the array should have
      the same length.
      <dl class="property required_ext">
        <dt class="property required_ext">Required property (first)</dt>
        <dd class="property required_ext">
          - `id` : integer
          - `atom-ids` : array of integers
        </dd>
      </dl>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property (second)</dt>
        <dd class="property required_ext">
          - `id` : integer
          - `xu` : float
          - `yu` : float
          - `zu` : float
        </dd>
      </dl>

    <span class="remove_in_table">
      GenDict objects are constructed
      taking each element of the `pairs`,
      and then put into #generators by #register_generators.
    </span>
  */
  ProTimeCorrelationInMolecule(
    const Vec<std::pair<ElPtr,ElPtr>> &pairs);
  virtual ~ProTimeCorrelationInMolecule() = default;
  /*!
    @brief Set initial vectors and resize #coefficients_traj.
    @return None.
  */
  virtual void prepare() override;
  /*!
    @brief Fill #coefficients_array with values of #coefficients_traj,
    and calculate #time_correlation_function by averaging over columns
    of #coefficients_array.

    @return None.

    Each row of #coefficients_array corresponds to
    each element of #coefficients_traj.
  */
  virtual void finish() override;
  /*!
    @brief Specify two atoms in a molecule by zero-based index.
    Time correlation function of a vector between the two atoms is
    computed for each molecule.

    @param index1_in_mol_
      A zero-based index in a molecule specifying a target atom.
      <span class="remove_in_table">
        This parameter is assigned to #index1_in_mol.
      </span>

    @param index2_in_mol_
      A zero-based index in a molecule
      specifying the other target atom.
      <span class="remove_in_table">
        This parameter is assigned to #index2_in_mol.
      </span>

    @return None.
  */
  void set_indices(
    int index1_in_mol_,
    int index2_in_mol_);
  /*!
    @brief Specify a molecular type. Only molecules whose `type`
    property is the specified type are analyzed. If molecules have
    no `type` property, you do not need to use this method.

    @param target_moltype_
      An integer for molecular type.
      <span class="remove_in_table">
        This parameter is assigned to #target_moltype.
      </span>

    @return None.
  */
  void set_moltype(
    int target_moltype_);
  /*!
    @brief Get a two-dimensional array containing
    computed time correlation coefficients of vectors
    connecting two atoms in the same molecule:
    each column is a time correlation function of atom-to-atom vector
    in each molecule.

    @return #coefficients_array.
  */
  const ArrayXXd &get_coefficients_array();
  /*!
    @brief Get an *averaged* time correlation function
    of atom-to-atom vector; each pair of atoms is in the same molecule.

    @return #time_correlation_function.
  */
  const ArrayXd &get_time_correlation();
};

#endif
