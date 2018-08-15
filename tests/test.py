import unittest

from test_StaDumpBox import TestStaDumpBox
from test_StaDumpAtoms import TestStaDumpAtoms
from test_StaMolecules import TestStaMolecules

from ppap4lmp import __version__

print("version: " + __version__)
print("\ntest starts...")

def suite():

  suite = unittest.TestSuite()

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

  #suite.addTest(TestStaDumpAtoms("test_error"))
  suite.addTest(TestStaMolecules("test_get_data"))
  suite.addTest(TestStaMolecules("test_get_keys"))

  return suite

if __name__ == "__main__":
  runner = unittest.TextTestRunner()
  runner.run(suite())
