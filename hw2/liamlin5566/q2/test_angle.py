import pytest
import math
import random
from _vector import calc_angle_in_python

def test_zero_len():
   
    assert math.isclose(calc_angle_in_python(0, 0, 0, 0), -100.0)
    
    assert math.isclose(calc_angle_in_python(1, 2, 0, 0), -100.0)
    

def test_zero_rad():
    assert math.isclose(calc_angle_in_python(1, 10, 1, 10), 0)
  
def test_half_pi():
    assert math.isclose(calc_angle_in_python(1, 0, 0, 1), 90*math.pi/180)

def test_other_vector():
    assert math.isclose(calc_angle_in_python(1, 0, -1, 1), math.acos(-1/math.sqrt(2)))

