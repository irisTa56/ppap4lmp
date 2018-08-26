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

tests = {
  "starter": suite_starter,
  #"filter": suite_filter,
  #"adder": suite_adder,
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
