import pytest
import math
import random
from _vector import calculate_angle_py

def test_zero_length():

    assert math.isclose(calculate_angle_py( x1 = 0, y1 = 0, x2 = 0, y2 = 0), -2.0)

def test_zero_angle():
    assert math.isclose(calculate_angle_py( x1 = 1, y1 = 0, x2 = 1, y2 = 0), 0.0)


def test_right_angle():
    assert math.isclose(calculate_angle_py( x1 = 1, y1 = 0, x2 = 0, y2 = 2), math.pi/2)

def test_other_angle():
    assert math.isclose(calculate_angle_py( x1 = 1, y1 = 0, x2 = -1, y2 = 0), math.pi)