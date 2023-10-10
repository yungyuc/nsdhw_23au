import _vector
import pytest
import math
from pytest import approx

v = [[1, 0], [0, 1], [-1, 0], [0, -1], [0, 0], [0, -3]]

def Rad2Degree(radian):
    degree = radian * (180/math.pi)
    return degree
   
def test_zeroLength():
    assert math.isnan(_vector.getAngle(v[4], v[4])) 

def test_zeroAngle():
    assert _vector.getAngle(v[0], v[0]) == approx(0)

def test_rightAngle():
    assert _vector.getAngle(v[0], v[1]) == approx(math.pi/2)

def test_otherAngle():
    assert _vector.getAngle(v[0], v[2]) == approx(math.pi)  
    assert _vector.getAngle(v[0], v[3]) == approx(math.pi/2)
    assert _vector.getAngle(v[1], v[2]) == approx(math.pi/2)
    assert _vector.getAngle(v[1], v[3]) == approx(math.pi)
    assert _vector.getAngle(v[2], v[5]) == approx(math.pi/2)
    
