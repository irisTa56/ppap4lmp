import unittest

from test_GenBoxDump import TestGenBoxDump
from test_GenAtomsDump import TestGenAtomsDump
from test_ProcData import TestProcData

from ppap4lmp import __version__

print("version: " + __version__)
print("\ntest starts...")


def suite():

  suite = unittest.TestSuite()

  suite.addTest(TestGenBoxDump("test_get_periodic"))
  suite.addTest(TestGenBoxDump("test_get_edge"))

  suite.addTest(TestGenAtomsDump("test_position_type"))
  suite.addTest(TestGenAtomsDump("test_get_positions"))
  suite.addTest(TestGenAtomsDump("test_get_data"))
  suite.addTest(TestGenAtomsDump("test_check_keys"))
  suite.addTest(TestGenAtomsDump("test_getters"))

  suite.addTest(TestProcData("test_with_2Boxes"))
  suite.addTest(TestProcData("test_with_2Atomses"))

  return suite


if __name__ == "__main__":
  runner = unittest.TextTestRunner()
  runner.run(suite())
