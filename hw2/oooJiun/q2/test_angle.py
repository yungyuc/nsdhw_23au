import math
from _vector import angle

def test_zero_len():
    assert math.isnan(angle((0, 0), (0, 0)))

def test_zero_angle():
    assert math.isclose(angle((1, 1), (2, 2)), 0, abs_tol = 1e-6)

def test_right_angle():
    assert math.isclose(angle((1, 0), (0, 1)), math.pi / 2, abs_tol = 1e-6)

def test_other_angle():
    assert math.isclose(angle((1, 2), (3, 0)), math.acos(3 / (math.sqrt(5) * math.sqrt(9))), abs_tol = 1e-6)