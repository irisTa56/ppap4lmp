import unittest

from test_ProData import TestProData
from test_ProValueArray import TestProValueArray
from test_ProThicknessProfile import TestProThicknessProfile
from test_ProRadialDistributionFunction import TestProRadialDistributionFunction
from test_ProRadialDistributionFunctionWithDeformation import TestProRadialDistributionFunctionWithDeformation
from test_ProDistanceInMolecule import TestProDistanceInMolecule
from test_ProMeanSquareDisplacement import TestProMeanSquareDisplacement

suite = unittest.TestSuite()

suite.addTest(TestProData("test_error01"))
suite.addTest(TestProData("test_without_select"))
suite.addTest(TestProData("test_with_select"))

suite.addTest(TestProValueArray("test_error01"))
suite.addTest(TestProValueArray("test_error02"))
suite.addTest(TestProValueArray("test_error03"))
suite.addTest(TestProValueArray("test_select_one"))
suite.addTest(TestProValueArray("test_select_two"))

suite.addTest(TestProThicknessProfile("test_error01"))
suite.addTest(TestProThicknessProfile("test_error02"))
suite.addTest(TestProThicknessProfile("test_20x30"))
suite.addTest(TestProThicknessProfile("test_20x30_with_offset"))
suite.addTest(TestProThicknessProfile("test_20x30_with_shift"))

suite.addTest(TestProRadialDistributionFunction("test_error01"))
suite.addTest(TestProRadialDistributionFunction("test_error02"))
suite.addTest(TestProRadialDistributionFunction("test_cubic"))
suite.addTest(TestProRadialDistributionFunction("test_cubic_bin_from_r_to_r_plus_dr"))
suite.addTest(TestProRadialDistributionFunction("test_cubic_beyond_half_box_length"))
suite.addTest(TestProRadialDistributionFunction("test_traj"))

suite.addTest(TestProRadialDistributionFunctionWithDeformation("test_error01"))
suite.addTest(TestProRadialDistributionFunctionWithDeformation("test_cubic_isotropic"))
suite.addTest(TestProRadialDistributionFunctionWithDeformation("test_cubic_same_size"))
suite.addTest(TestProRadialDistributionFunctionWithDeformation("test_with_and_without_modification"))

suite.addTest(TestProDistanceInMolecule("test_error01"))
suite.addTest(TestProDistanceInMolecule("test_error02"))
suite.addTest(TestProDistanceInMolecule("test_squared_distance"))
suite.addTest(TestProDistanceInMolecule("test_square_rooted_distance"))

suite.addTest(TestProMeanSquareDisplacement("test_error01"))
suite.addTest(TestProMeanSquareDisplacement("test_dimension_3d"))
suite.addTest(TestProMeanSquareDisplacement("test_dimension_2d"))
