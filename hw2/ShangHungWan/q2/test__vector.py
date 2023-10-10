import pytest
import _vector
import math


def test__vector_with_invalid_input():
    with pytest.raises(ValueError):
        _vector.calculate(0, 0, 0, 1)
    with pytest.raises(ValueError):
        _vector.calculate(0, 1, 0, 0)
    with pytest.raises(ValueError):
        _vector.calculate(0, 0, 0, 0)


def test__vector_calculator():
    assert _vector.calculate(1, 0, 1, 0) == 0
    assert _vector.calculate(1, 1, 2, 2) == 0
    assert _vector.calculate(1, 0, 1, 1) / math.pi * 180 == 45
    assert _vector.calculate(1, 0, 0, 1) / math.pi * 180 == 90
    assert _vector.calculate(1, 0, -1, 0) / math.pi * 180 == 180
