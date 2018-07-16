import unittest

from test_Element import TestElement
from test_Container import TestContainer
from test_ProData import TestProData
from test_ProValueArray import TestProValueArray

from ppap4lmp import __version__

print("version: " + __version__)
print("\ntest starts...")


def suite():

  suite = unittest.TestSuite()

  suite.addTest(TestElement("test_get_data"))
  suite.addTest(TestElement("test_getters"))
  suite.addTest(TestElement("test_filter"))
  suite.addTest(TestElement("test_molecules"))
  suite.addTest(TestElement("test_wrapped"))

  suite.addTest(TestContainer("test_list"))
  suite.addTest(TestContainer("test_dict"))

  suite.addTest(TestProData("test_with_Boxes"))
  suite.addTest(TestProData("test_with_Atomses"))

  suite.addTest(TestProValueArray("test_with_Atomses"))


  return suite


if __name__ == "__main__":
  runner = unittest.TextTestRunner()
  runner.run(suite())
