import math
from _vector import angle_py

def test_zero_len():
    assert math.isnan(angle_py((0, 0), (0, 0)))

def test_zero_angle():
    assert math.isclose(angle_py((1, 1), (2, 2)), 0)

def test_right_angle():
    assert angle_py((1, 0), (0, 1)) == math.pi / 2

def test_any_angle():
    assert angle_py((1, 2), (3, 4)) == math.acos(11 / (math.sqrt(5) * math.sqrt(25)))