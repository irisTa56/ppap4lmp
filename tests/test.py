import unittest

from test_GenBoxDump import TestGenBoxDump

from ppap4lmp import __version__

print("version: " + __version__)
print("\ntest starts...\n")


def suite():

  suite = unittest.TestSuite()
  suite.addTest(TestGenBoxDump("test_get_periodic"))
  suite.addTest(TestGenBoxDump("test_get_edge"))

  return suite


if __name__ == "__main__":
  runner = unittest.TextTestRunner()
  runner.run(suite())
