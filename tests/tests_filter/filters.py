import unittest

from test_FilSet import TestFilSet
from test_FilComparison import TestFilComparison

suite = unittest.TestSuite()

suite.addTest(TestFilSet("test_error01"))
suite.addTest(TestFilSet("test_equivalent_filter"))
suite.addTest(TestFilSet("test_remaining_number"))

suite.addTest(TestFilComparison("test_error01"))
suite.addTest(TestFilComparison("test_error02"))
suite.addTest(TestFilComparison("test_equivalent_filter"))
suite.addTest(TestFilComparison("test_remaining_number"))
suite.addTest(TestFilComparison("test_de_morgan"))