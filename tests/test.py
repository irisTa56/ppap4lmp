import unittest

from test_StaDumpBox import TestStaDumpBox

from ppap4lmp import __version__

print("version: " + __version__)
print("\ntest starts...")

def suite():

  suite = unittest.TestSuite()

  suite.addTest(TestStaDumpBox("test_error"))
  suite.addTest(TestStaDumpBox("test_get_data"))
  suite.addTest(TestStaDumpBox("test_get_keys"))

  return suite

if __name__ == "__main__":
  runner = unittest.TextTestRunner()
  runner.run(suite())
