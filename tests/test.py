import sys
import unittest

from ppap4lmp import __version__

print("version: " + __version__)

def suite_starter():

  from test_StaCustom import TestStaCustom

  print("\n[starter]")

  suite = unittest.TestSuite()

  suite.addTest(TestStaCustom("test_error01"))
  suite.addTest(TestStaCustom("test_get_data"))
  suite.addTest(TestStaCustom("test_get_keys"))

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
