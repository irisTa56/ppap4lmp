import unittest

from test_GenBoxDump import TestGenBoxDump
from test_ProcData import TestProcData

from ppap4lmp import __version__

print("version: " + __version__)
print("\ntest starts...")


def suite():

  suite = unittest.TestSuite()

  suite.addTest(TestGenBoxDump("test_get_periodic"))
  suite.addTest(TestGenBoxDump("test_get_edge"))

  suite.addTest(TestProcData("test_with_select"))
  suite.addTest(TestProcData("test_without_select"))

  return suite


if __name__ == "__main__":
  runner = unittest.TextTestRunner()
  runner.run(suite())
