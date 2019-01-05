import unittest

from test_AddMap import TestAddMap
from test_AddRename import TestAddRename
from test_AddWrappedPosition import TestAddWrappedPosition
from test_AddCoMPosition import TestAddCoMPosition
from test_AddInertiaMoment import TestAddInertiaMoment
from test_AddGyrationRadius import TestAddGyrationRadius
from test_AddMolecularOrientation import TestAddMolecularOrientation
from test_AddChildIDs import TestAddChildIDs
from test_AddChildPositions import TestAddChildPositions
from test_AddSpecialBonds import TestAddSpecialBonds
from test_AddBondLength import TestAddBondLength

suite = unittest.TestSuite()

suite.addTest(TestAddMap("test_error01"))
suite.addTest(TestAddMap("test_error02"))
suite.addTest(TestAddMap("test_nonarray"))
suite.addTest(TestAddMap("test_array"))
suite.addTest(TestAddMap("test_overwrite"))

suite.addTest(TestAddRename("test_error01"))
suite.addTest(TestAddRename("test_error02"))
suite.addTest(TestAddRename("test_error03"))
suite.addTest(TestAddRename("test_nonarray"))
suite.addTest(TestAddRename("test_array"))
suite.addTest(TestAddRename("test_overwrite"))

suite.addTest(TestAddWrappedPosition("test_error01"))
suite.addTest(TestAddWrappedPosition("test_error02"))
suite.addTest(TestAddWrappedPosition("test_wrapping"))

suite.addTest(TestAddCoMPosition("test_error01"))
suite.addTest(TestAddCoMPosition("test_positions"))
suite.addTest(TestAddCoMPosition("test_beads"))

suite.addTest(TestAddInertiaMoment("test_error01"))
suite.addTest(TestAddInertiaMoment("test_error02"))
suite.addTest(TestAddInertiaMoment("test_isotropic"))

suite.addTest(TestAddGyrationRadius("test_error01"))
suite.addTest(TestAddGyrationRadius("test_sqrted"))
suite.addTest(TestAddGyrationRadius("test_squared"))

suite.addTest(TestAddMolecularOrientation("test_error01"))
suite.addTest(TestAddMolecularOrientation("test_isotropic"))
suite.addTest(TestAddMolecularOrientation("test_x_oriented"))

suite.addTest(TestAddChildIDs("test_error01"))
suite.addTest(TestAddChildIDs("test_error02"))
suite.addTest(TestAddChildIDs("test_2way_molecules"))

suite.addTest(TestAddChildPositions("test_error01"))
suite.addTest(TestAddChildPositions("test_random"))
suite.addTest(TestAddChildPositions("test_gyration_radius"))

suite.addTest(TestAddSpecialBonds("test_error01"))
suite.addTest(TestAddSpecialBonds("test_error02"))
suite.addTest(TestAddSpecialBonds("test_exclude_angle"))

suite.addTest(TestAddBondLength("test_single_length"))
suite.addTest(TestAddBondLength("test_sequence_lengths"))
