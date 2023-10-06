import _vector
import pytest
import math


def cal_angle_python(v1: list, v2: list) -> float:
    dot_product = v1[0]*v2[0] + v1[1]*v2[1]
    length = math.sqrt(v1[0]**2 + v1[1]**2) \
            * math.sqrt(v2[0]**2 + v2[1]**2)
    if length == 0: return -1
    return math.acos(dot_product/length)

def test_zero_length():
    v1 = [0, 0]
    v2 = [1, 0]
    v3 = [0, 1]
    v4 = [1, 1]
    assert _vector.cal_angle(v1, v1) == cal_angle_python(v1, v2)
    assert _vector.cal_angle(v1, v2) == cal_angle_python(v1, v2)
    assert _vector.cal_angle(v1, v3) == cal_angle_python(v1, v2)
    assert _vector.cal_angle(v1, v4) == cal_angle_python(v1, v2)

def test_int_correctness():
    assert _vector.cal_angle([1,1], [2,2]) == pytest.approx(cal_angle_python([1,1], [2,2]))
    assert _vector.cal_angle([1,1], [1,0]) == pytest.approx(cal_angle_python([1,1], [1,0]))
    assert _vector.cal_angle([0,1], [1,0]) == pytest.approx(cal_angle_python([0,1], [1,0]))
    assert _vector.cal_angle([-1,0], [1,0]) == pytest.approx(cal_angle_python([-1,0], [1,0]))
    assert _vector.cal_angle([-1,0], [0,-1]) == pytest.approx(cal_angle_python([-1,0], [0,-1]))

def test_float_correctness():
    assert _vector.cal_angle([1.,1.], [2.,2.]) == pytest.approx(cal_angle_python([1.,1.], [2.,2.]))
    assert _vector.cal_angle([1.,1.], [1.,0.]) == pytest.approx(cal_angle_python([1.,1.], [1.,0.]))
    assert _vector.cal_angle([0.,1.], [1.,0.]) == pytest.approx(cal_angle_python([0.,1.], [1.,0.]))
    assert _vector.cal_angle([-1.,0.], [1.,0.]) == pytest.approx(cal_angle_python([-1.,0.], [1.,0.]))
    assert _vector.cal_angle([-1.,0.], [0.,-1.]) == pytest.approx(cal_angle_python([-1.,0.], [0.,-1.]))

def test_argument_correctness():
    with pytest.raises(TypeError):
        _vector.cal_angle([1,1])
        _vector.cal_angle()
        _vector.cal_angle([1,1,1])
        _vector.cal_angle([1,1], [1,1], [1,1])
        _vector.cal_angle(1,1)

if __name__ == '__main__': # you can test by the python
    test_zero_length()
    test_int_correctness()
    test_float_correctness()
    test_argument_correctness()