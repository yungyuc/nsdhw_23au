from _vector import get_angle_py
import math
import pytest

def test_zero_length():
    assert get_angle_py(0, 0, 0, 0) == 0

def test_zero_angle():
    assert get_angle_py(1, 2, 1, 2) == 0

def test_right_angle():
    assert math.isclose(get_angle_py(1, 0, 0, 1), (math.pi/2))

def test_other_angle():
    assert math.isclose(get_angle_py(1, 0, 1, 1), (math.pi/4))

