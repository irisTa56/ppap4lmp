import sys
import unittest

from ppap4lmp import __version__

print("version: " + __version__)

def suite_starter():

  from test_StaCustom import TestStaCustom
  from test_StaDumpAtoms import TestStaDumpAtoms
  from test_StaDumpBox import TestStaDumpBox
  from test_StaMolecules import TestStaMolecules
  from test_StaBeads import TestStaBeads

  print("\n[starter]")

  suite = unittest.TestSuite()

  suite.addTest(TestStaCustom("test_error01"))
  suite.addTest(TestStaCustom("test_get_data"))
  suite.addTest(TestStaCustom("test_get_keys"))

  suite.addTest(TestStaDumpAtoms("test_error01"))
  suite.addTest(TestStaDumpAtoms("test_get_data"))
  suite.addTest(TestStaDumpAtoms("test_get_keys"))
  suite.addTest(TestStaDumpAtoms("test_get_1d_int"))
  suite.addTest(TestStaDumpAtoms("test_get_1d_float"))
  suite.addTest(TestStaDumpAtoms("test_get_2d_int"))
  suite.addTest(TestStaDumpAtoms("test_get_2d_float"))

  suite.addTest(TestStaDumpBox("test_error01"))
  suite.addTest(TestStaDumpBox("test_get_data"))
  suite.addTest(TestStaDumpBox("test_get_keys"))

  suite.addTest(TestStaMolecules("test_error01"))
  suite.addTest(TestStaMolecules("test_get_data"))
  suite.addTest(TestStaMolecules("test_get_keys"))

  suite.addTest(TestStaBeads("test_error01"))
  suite.addTest(TestStaBeads("test_error02"))
  suite.addTest(TestStaBeads("test_error03"))
  suite.addTest(TestStaBeads("test_error04"))
  suite.addTest(TestStaBeads("test_atom_id"))

  return suite

def suite_filter():

  from test_FilSet import TestFilSet
  from test_FilComparison import TestFilComparison

  print("\n[filter]")

  suite = unittest.TestSuite()

  suite.addTest(TestFilSet("test_error01"))
  suite.addTest(TestFilSet("test_equivalent_filter"))
  suite.addTest(TestFilSet("test_remaining_number"))

  suite.addTest(TestFilComparison("test_error01"))
  suite.addTest(TestFilComparison("test_error02"))
  suite.addTest(TestFilComparison("test_equivalent_filter"))
  suite.addTest(TestFilComparison("test_remaining_number"))
  suite.addTest(TestFilComparison("test_de_morgan"))

  return suite

def suite_adder():

  from test_AddMap import TestAddMap
  from test_AddRename import TestAddRename
  from test_AddWrappedPositions import TestAddWrappedPositions
  from test_AddCoMPositions import TestAddCoMPositions
  from test_AddInertiaMoment import TestAddInertiaMoment
  from test_AddGyrationRadius import TestAddGyrationRadius
  from test_AddMolecularOrientation import TestAddMolecularOrientation
  from test_AddChildIDs import TestAddChildIDs
  from test_AddSpecialBonds import TestAddSpecialBonds

  print("\n[adder]")

  suite = unittest.TestSuite()

  suite.addTest(TestAddMap("test_error01"))
  suite.addTest(TestAddMap("test_error02"))
  suite.addTest(TestAddMap("test_nonarray"))
  suite.addTest(TestAddMap("test_array"))
  suite.addTest(TestAddMap("test_overwrite"))

  suite.addTest(TestAddRename("test_error01"))
  suite.addTest(TestAddRename("test_error02"))
  suite.addTest(TestAddRename("test_error03"))
  suite.addTest(TestAddRename("test_nonarray"))
  suite.addTest(TestAddRename("test_array"))
  suite.addTest(TestAddRename("test_overwrite"))

  suite.addTest(TestAddWrappedPositions("test_error01"))
  suite.addTest(TestAddWrappedPositions("test_error02"))
  suite.addTest(TestAddWrappedPositions("test_wrapping"))

  suite.addTest(TestAddCoMPositions("test_error01"))
  suite.addTest(TestAddCoMPositions("test_positions"))
  suite.addTest(TestAddCoMPositions("test_beads"))

  suite.addTest(TestAddInertiaMoment("test_error01"))
  suite.addTest(TestAddInertiaMoment("test_error02"))
  suite.addTest(TestAddInertiaMoment("test_isotropic"))

  suite.addTest(TestAddGyrationRadius("test_error01"))
  suite.addTest(TestAddGyrationRadius("test_sqrted"))
  suite.addTest(TestAddGyrationRadius("test_squared"))

  suite.addTest(TestAddMolecularOrientation("test_error01"))
  suite.addTest(TestAddMolecularOrientation("test_isotropic"))
  suite.addTest(TestAddMolecularOrientation("test_x_oriented"))

  suite.addTest(TestAddChildIDs("test_error01"))
  suite.addTest(TestAddChildIDs("test_error02"))
  suite.addTest(TestAddChildIDs("test_2way_molecules"))

  suite.addTest(TestAddSpecialBonds("test_error01"))
  suite.addTest(TestAddSpecialBonds("test_error02"))
  suite.addTest(TestAddSpecialBonds("test_exclude_angle"))

  return suite

tests = {
  "starter": suite_starter,
  "filter": suite_filter,
  "adder": suite_adder,
  #"proc": suite_proc
}

if __name__ == "__main__":

  args = sys.argv
  runner = unittest.TextTestRunner()
  targets = []

  if len(args) == 1 or args[1] == "all":
    targets.extend(list(tests.keys()))
  else:
    targets.extend([arg for arg in args[1:] if arg in tests.keys()])

  for t in targets:
    runner.run(tests[t]())
