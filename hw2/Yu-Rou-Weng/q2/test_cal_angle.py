import _vector
import math
import pytest

def test_zerolength_2Dvector():
    """
    Test for zero-length 2-vector (invalid input)
    """
    assert(math.isnan(_vector.AngleBtwVectors(0, 0, 0,0)))

def test_zero_angle():
    """
    Test for zero angle
    """
    assert(_vector.AngleBtwVectors(2,3,4,6)==0)

def test_right_angle():
    """
    Test for right angle (90-deg)
    """
    assert math.isclose(_vector.AngleBtwVectors(2, 1, 1, -2),math.pi/2,abs_tol=1e-9, rel_tol=1e-9)

def test_arbitrary_angle():
    """
    Test for one other angle
    """
    assert math.isclose(_vector.AngleBtwVectors(1, 1, 0, 1), math.pi/4, abs_tol=1e-9, rel_tol=1e-9)
    assert math.isclose(_vector.AngleBtwVectors(1, 0, -1, 0), math.pi, abs_tol=1e-9, rel_tol=1e-9)
    #assert math.isclose(cal_angle.AngleBtwVectors(1, math.sqrt(3), 1/2, math.sqrt(3)/2), 0.523599, abs_tol=1e-9, rel_tol=1e-9)