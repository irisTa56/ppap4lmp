import unittest

from test_GenElement import TestGenElement
from test_ProData import TestProData

from ppap4lmp import __version__

print("version: " + __version__)
print("\ntest starts...")


def suite():

  suite = unittest.TestSuite()

  suite.addTest(TestGenElement("test_get_data"))
  suite.addTest(TestGenElement("test_check_keys"))
  suite.addTest(TestGenElement("test_getters"))

  suite.addTest(TestProData("test_with_2Boxes"))
  suite.addTest(TestProData("test_with_2Atomses"))

  return suite


if __name__ == "__main__":
  runner = unittest.TextTestRunner()
  runner.run(suite())
