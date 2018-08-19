import sys
import unittest

from test_StaCustom import TestStaCustom
from test_StaDumpBox import TestStaDumpBox
from test_StaDumpAtoms import TestStaDumpAtoms
from test_StaMolecules import TestStaMolecules
from test_StaBeads import TestStaBeads

from test_FilSet import TestFilSet
from test_FilComparison import TestFilComparison

from test_AddMap import TestAddMap
from test_AddRename import TestAddRename
from test_AddWrappedPositions import TestAddWrappedPositions
from test_AddCoMPositions import TestAddCoMPositions
from test_AddInertiaMoment import TestAddInertiaMoment
from test_AddGyrationRadius import TestAddGyrationRadius
from test_AddMolecularOrientation import TestAddMolecularOrientation
from test_AddChildIDs import TestAddChildIDs
from test_AddSpecialBonds import TestAddSpecialBonds

from test_ProData import TestProData
from test_ProValueArray import TestProValueArray
from test_ProThicknessProfile import TestProThicknessProfile

from ppap4lmp import __version__

print("version: " + __version__)

def suite_starter():

  print("\n[starter]")

  suite = unittest.TestSuite()

  suite.addTest(TestStaCustom("test_error"))
  suite.addTest(TestStaCustom("test_get_data"))
  suite.addTest(TestStaCustom("test_get_keys"))

  suite.addTest(TestStaDumpBox("test_error"))
  suite.addTest(TestStaDumpBox("test_get_data"))
  suite.addTest(TestStaDumpBox("test_get_keys"))

  suite.addTest(TestStaDumpAtoms("test_error"))
  suite.addTest(TestStaDumpAtoms("test_get_data"))
  suite.addTest(TestStaDumpAtoms("test_get_keys"))
  suite.addTest(TestStaDumpAtoms("test_get_1d_int"))
  suite.addTest(TestStaDumpAtoms("test_get_1d_double"))
  suite.addTest(TestStaDumpAtoms("test_get_2d_int"))
  suite.addTest(TestStaDumpAtoms("test_get_2d_double"))

  suite.addTest(TestStaDumpAtoms("test_error"))
  suite.addTest(TestStaMolecules("test_get_data"))
  suite.addTest(TestStaMolecules("test_get_keys"))

  suite.addTest(TestStaBeads("test_error"))
  suite.addTest(TestStaBeads("test_atom_id"))

  return suite

def suite_filter():

  print("\n[filter]")

  suite = unittest.TestSuite()

  suite.addTest(TestFilSet("test_error"))
  suite.addTest(TestFilSet("test_equivalent_filter"))
  suite.addTest(TestFilSet("test_remaining_number"))

  suite.addTest(TestFilComparison("test_error"))
  suite.addTest(TestFilComparison("test_equivalent_filter"))
  suite.addTest(TestFilComparison("test_remaining_number"))
  suite.addTest(TestFilComparison("test_de_morgan"))

  return suite

def suite_adder():

  print("\n[adder]")

  suite = unittest.TestSuite()

  suite.addTest(TestAddMap("test_error"))
  suite.addTest(TestAddMap("test_nonarray"))
  suite.addTest(TestAddMap("test_array"))

  suite.addTest(TestAddRename("test_error"))
  suite.addTest(TestAddRename("test_nonarray"))
  suite.addTest(TestAddRename("test_array"))

  suite.addTest(TestAddWrappedPositions("test_error"))
  suite.addTest(TestAddWrappedPositions("test_wrapping"))

  suite.addTest(TestAddCoMPositions("test_error"))
  suite.addTest(TestAddCoMPositions("test_positions"))
  suite.addTest(TestAddCoMPositions("test_beads"))

  suite.addTest(TestAddInertiaMoment("test_error"))
  suite.addTest(TestAddInertiaMoment("test_isotropic"))

  suite.addTest(TestAddGyrationRadius("test_error"))
  suite.addTest(TestAddGyrationRadius("test_isotropic"))

  suite.addTest(TestAddMolecularOrientation("test_error"))
  suite.addTest(TestAddMolecularOrientation("test_isotropic"))
  suite.addTest(TestAddMolecularOrientation("test_x_oriented"))

  suite.addTest(TestAddChildIDs("test_error"))
  suite.addTest(TestAddChildIDs("test_2way_molecules"))

  suite.addTest(TestAddSpecialBonds("test_error"))
  suite.addTest(TestAddSpecialBonds("test_exclude_angle"))

  return suite

def suite_procs():

  print("\n[procs]")

  suite = unittest.TestSuite()

  suite.addTest(TestProData("test_error"))
  suite.addTest(TestProData("test_without_select"))
  suite.addTest(TestProData("test_with_select"))

  suite.addTest(TestProValueArray("test_error"))
  suite.addTest(TestProValueArray("test_select_one"))
  suite.addTest(TestProValueArray("test_select_two"))

  suite.addTest(TestProThicknessProfile("test_error"))
  suite.addTest(TestProThicknessProfile("test_20x30"))
  suite.addTest(TestProThicknessProfile("test_20x30_with_offset"))
  suite.addTest(TestProThicknessProfile("test_20x30_with_shift"))

  return suite

tests = {
  "starter": suite_starter,
  "filter": suite_filter,
  "adder": suite_adder,
  "procs": suite_procs
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
