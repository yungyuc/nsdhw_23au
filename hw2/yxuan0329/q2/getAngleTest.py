import _vector
import pytest
import math

def getAngleTest():
    v = [[1, 0], [0, 1], [-1, 0], [0, -1]]

    assert Rad2Angle(getAngle(v[0], v[1])) == 90
    assert Rad2Angle(getAngle(v[0], v[2])) == 180    
    assert Rad2Angle(getAngle(v[0], v[3])) == 90
    assert Rad2Angle(getAngle(v[1], v[2])) == 90
    assert Rad2Angle(getAngle(v[1], v[3])) == 180
    assert Rad2Angle(getAngle(v[2], v[3])) == 90
    assert Rad2Angle(getAngle(v[0], v[0])) == 0
