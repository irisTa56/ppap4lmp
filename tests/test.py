import sys
import unittest

from ppap4lmp import __version__

print("version: " + __version__)

def suite_starter():

  print("\n[starter]")

  sys.path.append("tests_starter")

  from starters import suite

  return suite

def suite_filter():

  print("\n[filter]")

  sys.path.append("tests_filter")

  from filters import suite

  return suite

def suite_adder():

  print("\n[adder]")

  sys.path.append("tests_adder")

  from adders import suite

  return suite

def suite_processor():

  print("\n[processor]")

  sys.path.append("tests_processor")

  from processor import suite

  return suite

tests = {
  "starter": suite_starter,
  "filter": suite_filter,
  "adder": suite_adder,
  "processor": suite_processor
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
