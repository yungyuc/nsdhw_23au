import math
from _vector import calculate_angle
import pytest


def test_zero_len():
    assert math.isnan(calculate_angle((0, 0), (0, 0)))


def test_zero_angle():
    v1 = (1, 1)
    v2 = (2, 2)
    assert math.isclose(calculate_angle(v1, v2), 0, abs_tol = 1e-6)


def test_right_angle():
    v1 = (2, 1)
    v2 = (1, -2)
    assert math.isclose(calculate_angle(v1, v2), math.pi/2, rel_tol=1e-9,abs_tol = 1e-9)

def test_calculate_angle():
    v1 = (1, 1)
    v2 = (0, 1)
    assert math.isclose(calculate_angle(v1, v2), math.pi/4, rel_tol=1e-9,abs_tol = 1e-9)

