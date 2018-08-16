import unittest

from test_StaCustom import TestStaCustom
from test_StaDumpBox import TestStaDumpBox
from test_StaDumpAtoms import TestStaDumpAtoms
from test_StaMolecules import TestStaMolecules
from test_FilSet import TestFilSet
from test_FilComparison import TestFilComparison

from ppap4lmp import __version__

print("version: " + __version__)
print("\ntest starts...")

def suite():

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

  suite.addTest(TestFilSet("test_error"))
  suite.addTest(TestFilSet("test_equivalent_filter"))
  suite.addTest(TestFilSet("test_remaining_number"))

  suite.addTest(TestFilComparison("test_error"))
  suite.addTest(TestFilComparison("test_equivalent_filter"))
  suite.addTest(TestFilComparison("test_remaining_number"))
  suite.addTest(TestFilComparison("test_de_morgan"))

  return suite

if __name__ == "__main__":
  runner = unittest.TextTestRunner()
  runner.run(suite())
