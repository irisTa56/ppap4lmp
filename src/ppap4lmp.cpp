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

  @code{.bash}
    conda install -c irista56 ppap4lmp
  @endcode

  For more details, please see
  <a href="https://github.com/irisTa56/ppap4lmp#installation">GitHub repository</a>.

  @section feat_sec Features

  - Implemented by C++, Used from Python
  - Data stored in Json structure
  - Extensible without editing existing codes

  @section diagram_sec Schematic Sequence Diagram

  @htmlonly
    <script src="js/mermaid.min.js"></script>
    <script>mermaid.initialize({startOnLoad:true});</script>

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

  @subsection python_sec_element For Element

  @copydetails src/pybind/py_element.h

  @subsection python_sec_starter For Starter: Updater for initializing an Element object

  @copydetails src/pybind/starters/py_sta_beads.h
  @copydetails src/pybind/starters/py_sta_copy.h
  @copydetails src/pybind/starters/py_sta_custom.h
  @copydetails src/pybind/starters/py_sta_dump_atoms.h
  @copydetails src/pybind/starters/py_sta_dump_box.h
  @copydetails src/pybind/starters/py_sta_molecules.h

  @subsection python_sec_adder For Adder: Updater for adding new properties to an Element object

  @copydetails src/pybind/adders/py_add_child_ids.h
  @copydetails src/pybind/adders/py_add_child_positions.h
  @copydetails src/pybind/adders/py_add_com_position.h
  @copydetails src/pybind/adders/py_add_gyration_radius.h
  @copydetails src/pybind/adders/py_add_inertia_moment.h
  @copydetails src/pybind/adders/py_add_map.h
  @copydetails src/pybind/adders/py_add_molecular_orientation.h
  @copydetails src/pybind/adders/py_add_rename.h
  @copydetails src/pybind/adders/py_add_special_bonds.h
  @copydetails src/pybind/adders/py_add_wrapped_position.h

  @subsection python_sec_adder For Filter: Updater for filtering against an Element object

  @copydetails src/pybind/filters/py_fil_comparison.h
  @copydetails src/pybind/filters/py_fil_set.h

  @section property_sec List of Properties

  @note Key for externally required property means that the key must be in Element::datakeys of Updater::ext_generator.

  @copydetails StaBeads::compute_impl
  @copydetails StaDumpAtoms::compute_impl
  @copydetails StaDumpBox::compute_impl
  @copydetails StaMolecules::compute_impl
  <br/>
  @copydetails AddChildIDs::compute_impl
  @copydetails AddChildPositions::compute_impl
  @copydetails AddCoMPosition::compute_impl
  @copydetails AddGyrationRadius::compute_impl
  @copydetails AddInertiaMoment::compute_impl
  @copydetails AddMap::compute_impl
  @copydetails AddMolecularOrientation::compute_impl
  @copydetails AddRename::compute_impl
  @copydetails AddSpecialBonds::compute_impl
  @copydetails AddWrappedPosition::compute_impl

  @section acknowledge_sec Acknowledgement

  This project would not be possible without the following great open-source projects.

  - <a href="https://github.com/pybind/pybind11">pybind11</a>
  - <a href="https://github.com/nlohmann/json">nlohmann/json</a>
  - <a href="http://eigen.tuxfamily.org/index.php?title=Main_Page">Eigen</a>
 */
