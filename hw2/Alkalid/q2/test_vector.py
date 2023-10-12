import _vector as vector
import math
import pytest

def test_calc_zero_in_python():
    angle = vector.calc_angle_in_python(1, 0, 1, 0)
    assert angle == 0

def test_calc_90_in_python():
    angle = vector.calc_angle_in_python(1, 0, 1, 0)
    assert angle == 0

def test_calc_inverse_in_python():
    angle = vector.calc_angle_in_python(1, 0, -1, 0)
    assert math.isclose(angle, math.pi, rel_tol=1e-9)
    

def test_calc_angle_in_python():
    angle = vector.calc_angle_in_python(1, 0, 0, 1)
    assert abs(angle - 1.5708) < 0.001  # π/2 ≈ 1.5708