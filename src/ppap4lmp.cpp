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

  This project is named \c ppap4lmp,
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

  - Implemented by C++, Used from Python
  - Data stored in Json structure
  - Extensible without editing existing codes

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

      user ->> inv : create with Processor objects

      note over inv : Store the Processor objects

      inv -->> user : object

      user ->> inv : execute

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

  @section python_sec Functions accessible from Python

  @subsection python_sec_element Element

  @copydetails pybind::py_element

  @subsection python_sec_starter Starter

  Starter is an Updater's subclass for initializing an Element object.

  @copydetails pybind::py_sta_beads
  @copydetails pybind::py_sta_copy
  @copydetails pybind::py_sta_custom
  @copydetails pybind::py_sta_dump_atoms
  @copydetails pybind::py_sta_dump_box
  @copydetails pybind::py_sta_molecules

  @subsection python_sec_adder Adder

  Adder is an Updater's subclass for adding new properties to an Element object.

  @copydetails pybind::py_add_child_ids
  @copydetails pybind::py_add_child_positions
  @copydetails pybind::py_add_com_position
  @copydetails pybind::py_add_gyration_radius
  @copydetails pybind::py_add_inertia_moment
  @copydetails pybind::py_add_map
  @copydetails pybind::py_add_molecular_orientation
  @copydetails pybind::py_add_rename
  @copydetails pybind::py_add_special_bonds
  @copydetails pybind::py_add_wrapped_position

  @subsection python_sec_filter Filter

  Filter is an Updater's subclass for filtering against an Element object.

  @copydetails pybind::py_fil_comparison
  @copydetails pybind::py_fil_set

  @subsection python_sec_proc Processor

  @copydetails pybind::py_pro_data

  @subsection python_sec_invo Invoker

  @copydetails pybind::py_inv_omp

  @subsection python_sec_utils Utility functions

  @copydetails pybind::py_utils

  @section acknowledge_sec Acknowledgement

  This project would not be possible
  without the following great open-source projects.

  - <a href="https://github.com/pybind/pybind11">pybind11</a>
  - <a href="https://github.com/nlohmann/json">nlohmann/json</a>
  - <a href="http://eigen.tuxfamily.org/index.php?title=Main_Page">Eigen</a>

  <hr/>

  @author Takayuki Kobayashi
  @copyright MIT License
  @date 2018
 */
