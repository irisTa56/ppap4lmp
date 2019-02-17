/*!
  @file src/ppap4lmp.cpp
  @brief This file has no implementation, only includes a header file
  to bind C++ and Python.
  @author Takayuki Kobayashi
  @date 2018/09/08
*/

#include "pybind.h"

/*!
  @mainpage ppap4lmp documentation

  @section intro_sec Introduction

  This project is named `ppap4lmp`,
  which stands for PostProcess and Analysis Program for LAMMPS.

  GitHub repository is
  <a href="https://github.com/irisTa56/ppap4lmp">here</a>.

  @section install_sec Installation

  Via Conda.

  @htmlonly
  <pre class="prettyprint"><code class="lang-sh"># shell
  conda install -c irista56 ppap4lmp
  </code></pre>
  @endhtmlonly

  For more details, please see
  <a href="https://github.com/irisTa56/ppap4lmp#installation">GitHub repository</a>.

  @section feat_sec Features

  - Implemented by C++, Used from Python.
  - Data stored in JSON structure.
  - Extensible without editing existing codes.

  @section diagram_sec Schematic Sequence Diagram

  @htmlonly
  <div class="mermaid">
    sequenceDiagram

    participant user as User (Python)
    participant ele as Element
    participant upd as Updater's subclass
    participant pro as Processor's subclass
    participant inv as Invoker's subclass

    user ->> upd : create Starter (Uptater for initialization)
    upd -->> user : object
    user ->> ele : create with the Starter object

    note over ele,upd : UpdatePair (pair of Element and Updater) is stored in the Element object.

    ele -->> user : object

    loop additional properties
      user ->> upd : create Adder (Uptater for adding new properties)
      upd -->> user : object
      user ->> ele : append the Adder object
      note over ele,upd : UpdatePair (pair of Element and Updater) is stored the Element object.
    end

    user ->> pro : create with Generator objects

    note over pro : Store the Generator objects

    pro -->> user : object

    user ->> inv : execute with Processor objects

    loop over Generator objects
      inv ->> pro : run
      pro ->> ele : execute updating process
      note over ele,upd : Chain of UpdatePair objects is executed one by one (the Element objects updates their data using the paired Updater objects).
      ele -->> pro : updated data can be accessed
      note over pro : Run analysis process for each Generator object using the data.
    end

    pro -->> user : get results
  </div>
  @endhtmlonly

  @section acknowledge_sec Acknowledgement

  This project would not be possible
  without the following great open-source projects.

  - <a href="https://github.com/pybind/pybind11">pybind11</a>
  - <a href="https://github.com/nlohmann/json">nlohmann/json</a>
  - <a href="http://eigen.tuxfamily.org/index.php?title=Main_Page">Eigen</a>

  @section python_sec Class accessible from Python

  @subsection python_sec_element Element
  @copybrief Element
  @copydetails pybind::py_element



  @subsection python_sec_starter Starter
  @copybrief Starter

  @subsubsection python_sec_sta_beads StaBeads
  @copybrief StaBeads
  @copydetails pybind::py_sta_beads

  @subsubsection python_sec_sta_copy StaCopy
  @copybrief StaCopy
  @copydetails pybind::py_sta_copy

  @subsubsection python_sec_sta_custom StaCustom
  @copybrief StaCustom
  @copydetails pybind::py_sta_custom

  @subsubsection python_sec_sta_dump_atoms StaDumpAtoms
  @copybrief StaDumpAtoms
  @copydetails pybind::py_sta_dump_atoms

  @subsubsection python_sec_sta_dump_box StaDumpBox
  @copybrief StaDumpBox
  @copydetails pybind::py_sta_dump_box

  @subsubsection python_sec_sta_molecules StaMolecules
  @copybrief StaMolecules
  @copydetails pybind::py_sta_molecules



  @subsection python_sec_adder Adder
  @copybrief Adder

  @subsubsection python_py_add_bond_angle AddBondAngle
  @copybrief AddBondAngle
  @copydetails pybind::py_add_bond_angle

  @subsubsection python_py_add_bond_length AddBondLength
  @copybrief AddBondLength
  @copydetails pybind::py_add_bond_length

  @subsubsection python_py_add_child_ids AddChildIDs
  @copybrief AddChildIDs
  @copydetails pybind::py_add_child_ids

  @subsubsection python_py_add_child_positions AddChildPositions
  @copybrief AddChildPositions
  @copydetails pybind::py_add_child_positions

  @subsubsection python_py_add_com_position AddCoMPosition
  @copybrief AddCoMPosition
  @copydetails pybind::py_add_com_position

  @subsubsection python_py_add_dihedral_angle AddDihedralAngle
  @copybrief AddDihedralAngle
  @copydetails pybind::py_add_dihedral_angle

  @subsubsection python_py_add_gyration_radius AddGyrationRadius
  @copybrief AddGyrationRadius
  @copydetails pybind::py_add_gyration_radius

  @subsubsection python_py_add_inertia_moment AddInertiaMoment
  @copybrief AddInertiaMoment
  @copydetails pybind::py_add_inertia_moment

  @subsubsection python_py_add_map AddMap
  @copybrief AddMap
  @copydetails pybind::py_add_map

  @subsubsection python_py_add_molecular_orientation AddMolecularOrientation
  @copybrief AddMolecularOrientation
  @copydetails pybind::py_add_molecular_orientation

  @subsubsection python_py_add_rename AddRename
  @copybrief AddRename
  @copydetails pybind::py_add_rename

  @subsubsection python_py_add_special_bonds AddSpecialBonds
  @copybrief AddSpecialBonds
  @copydetails pybind::py_add_special_bonds

  @subsubsection python_py_add_wrapped_position AddWrappedPosition
  @copybrief AddWrappedPosition
  @copydetails pybind::py_add_wrapped_position



  @subsection python_sec_filter Filter
  @copybrief Filter

  @subsubsection python_py_fil_comparison FilComparison
  @copybrief FilComparison
  @copydetails pybind::py_fil_comparison

  @subsubsection python_py_fil_set FilSet
  @copybrief FilSet
  @copydetails pybind::py_fil_set



  @subsection python_sec_proc Processor
  @copybrief Processor

  @subsubsection python_py_pro_data ProData
  @copybrief ProData
  @copydetails pybind::py_pro_data

  @subsubsection python_py_pro_distance_in_molecule ProDistanceInMolecule
  @copybrief ProDistanceInMolecule
  @copydetails pybind::py_pro_distance_in_molecule

  @subsubsection python_py_pro_mean_square_displacement ProMeanSquareDisplacement
  @copybrief ProMeanSquareDisplacement
  @copydetails pybind::py_pro_mean_square_displacement

  @subsubsection python_py_pro_radial_distribution_function ProRadialDistributionFunction
  @copybrief ProRadialDistributionFunction
  @copydetails pybind::py_pro_radial_distribution_function

  @subsubsection python_py_pro_radial_distribution_function_with_deformation ProRadialDistributionFunctionWithDeformation
  @copybrief ProRadialDistributionFunctionWithDeformation
  @copydetails pybind::py_pro_radial_distribution_function_with_deformation

  @subsubsection python_py_pro_thickness_profile ProThicknessProfile
  @copybrief ProThicknessProfile
  @copydetails pybind::py_pro_thickness_profile

  @subsubsection python_py_pro_time_correlation_in_molecule ProTimeCorrelationInMolecule
  @copybrief ProTimeCorrelationInMolecule
  @copydetails pybind::py_pro_time_correlation_in_molecule

  @subsubsection python_py_pro_value_array ProValueArray
  @copybrief ProValueArray
  @copydetails pybind::py_pro_value_array


  @subsection python_sec_invo Invoker
  @copybrief Invoker

  @subsubsection python_py_inv_omp InvOMP
  @copybrief InvOMP
  @copydetails pybind::py_inv_omp



  @subsection python_sec_utils Utilities

  @copydetails pybind::py_utils



  @section property_list_sec Properties To Be Added

  <table class="properties_list">
    <tr>
      <th class="properties_list">Class</th>
      <th class="properties_list" colspan="4">Property Names</th>
    </tr>
  </table>

  <hr/>

  @author Takayuki Kobayashi
  @copyright MIT License
  @date 2018
 */
