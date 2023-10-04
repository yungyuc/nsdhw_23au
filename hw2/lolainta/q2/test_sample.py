from _vector import magic
import math


def test_magic():
    t1 = magic([], [])
    assert math.isnan(t1), t1
    t2 = magic([1, 2, 3], [2, 4, 6])
    assert math.isclose(t2, 0), t2
    t3 = magic([1, 0], [0, 1])
    assert math.isclose(t3, math.pi / 2), t3
    t4 = magic([1, 0], [1, math.sqrt(3)])
    assert math.isclose(t4, math.pi / 3), t4
