import pytest
import math
from _vector import calculateAngle

# Test for zero-length 2-vector (invalid input).
def test_zero_length():
    with pytest.raises(Exception):
        calculateAngle([0, 0], [1, 1])
    
# Test for zero angle.
def test_zero_angle():
    assert math.isnan(calculateAngle([2, 2], [1, 1]))

# Test for right angle (90-deg).
def test_right_angle():
    assert calculateAngle([0, 1], [1, 0]) == pytest.approx(math.pi/2)
    # print("test_right_angle")

# Test for one other angle.
def test_other_angle():     # 180
    assert calculateAngle([-2, 0], [2, 0]) == pytest.approx(math.pi)
    # print("test_other_angle")

test_zero_length()
test_zero_angle()
test_right_angle()
test_other_angle()