import unittest

from test_Element import TestElement
from test_Container import TestContainer
from test_ProData import TestProData

from ppap4lmp import __version__

print("version: " + __version__)
print("\ntest starts...")


def suite():

  suite = unittest.TestSuite()

  suite.addTest(TestElement("test_get_data"))
  suite.addTest(TestElement("test_check_keys"))
  suite.addTest(TestElement("test_getters"))
  suite.addTest(TestElement("test_filter"))

  suite.addTest(TestContainer("test_list"))
  suite.addTest(TestContainer("test_dict"))

  suite.addTest(TestProData("test_with_Boxes"))
  suite.addTest(TestProData("test_with_Atomses"))
  suite.addTest(TestProData("test_with_Atomses_oneUpdater"))

  return suite


if __name__ == "__main__":
  runner = unittest.TextTestRunner()
  runner.run(suite())
