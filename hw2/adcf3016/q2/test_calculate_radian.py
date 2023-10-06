# Naming convention reference: https://google.github.io/styleguide/pyguide.html

import _vector
import pytest
import math

def test_nan():
    assert math.isnan(_vector.calculate_radian(0, 0, 1, 1))

def test_zero_angle():
    assert abs(_vector.calculate_radian(0, 1, 0, 2) - 0) < 10e-6

def test_right_angle():
    assert abs(_vector.calculate_radian(0, 1, 2, 0) - math.pi/2) < 10e-6

def test_other_angle():
    assert abs(_vector.calculate_radian(2, 2, 1, 0) - math.pi/4) < 10e-6
