import unittest

from test_StaCustom import TestStaCustom
from test_StaCopy import TestStaCopy
from test_StaDumpAtoms import TestStaDumpAtoms
from test_StaDumpBox import TestStaDumpBox
from test_StaMolecules import TestStaMolecules
from test_StaBeads import TestStaBeads

suite = unittest.TestSuite()

suite.addTest(TestStaCustom("test_error01"))
suite.addTest(TestStaCustom("test_get_data"))
suite.addTest(TestStaCustom("test_get_keys"))
suite.addTest(TestStaCustom("test_short_form"))

suite.addTest(TestStaCopy("test_get_data"))
suite.addTest(TestStaCopy("test_get_keys"))
suite.addTest(TestStaCopy("test_short_form"))

suite.addTest(TestStaDumpAtoms("test_error01"))
suite.addTest(TestStaDumpAtoms("test_get_data"))
suite.addTest(TestStaDumpAtoms("test_get_keys"))
suite.addTest(TestStaDumpAtoms("test_get_1d_int"))
suite.addTest(TestStaDumpAtoms("test_get_1d_float"))
suite.addTest(TestStaDumpAtoms("test_get_2d_int"))
suite.addTest(TestStaDumpAtoms("test_get_2d_float"))

suite.addTest(TestStaDumpBox("test_error01"))
suite.addTest(TestStaDumpBox("test_get_data"))
suite.addTest(TestStaDumpBox("test_get_keys"))

suite.addTest(TestStaMolecules("test_error01"))
suite.addTest(TestStaMolecules("test_get_data"))
suite.addTest(TestStaMolecules("test_get_keys"))

suite.addTest(TestStaBeads("test_error01"))
suite.addTest(TestStaBeads("test_error02"))
suite.addTest(TestStaBeads("test_error03"))
suite.addTest(TestStaBeads("test_error04"))
suite.addTest(TestStaBeads("test_atom_id"))
