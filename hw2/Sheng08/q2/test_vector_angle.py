import _vector
import pytest
import math


def test_orthogonal_vectors():
    v1 = (1.0, 0.0)
    v2 = (0.0, 1.0)
    assert _vector.calculate_angle(v1, v2) == pytest.approx(
        math.pi/2, rel=1e-5)    # math.isclose()


def test_parallel_vectors():
    v1 = (1.0, 0.0)
    v2 = (1.0, 0.0)
    assert _vector.calculate_angle(v1, v2) == pytest.approx(0.0, rel=1e-5)


def test_opposite_vectors():
    v1 = (1.0, 0.0)
    v2 = (-1.0, 0.0)
    assert _vector.calculate_angle(v1, v2) == pytest.approx(math.pi, rel=1e-5)


def test_zero_vector():
    v1 = (0.0, 0.0)
    v2 = (1.0, 1.0)
    assert math.isnan(_vector.calculate_angle(v1, v2))


def test_zero_length():
    v1 = (0.0, 0.0)
    v2 = (1.0, 0.0)
    assert math.isnan(_vector.calculate_angle(v1, v1))
    assert math.isnan(_vector.calculate_angle(v1, v2))


def test_zero_angle():
    v1 = (1.0, 0.0)
    v2 = (1.0, 0.0)
    assert _vector.calculate_angle(v1, v2) == pytest.approx(0.0, rel=1e-5)


def test_right_angle():
    v1 = (1.0, 0.0)
    v2 = (0.0, 1.0)
    assert _vector.calculate_angle(
        v1, v2) == pytest.approx(math.pi/2, rel=1e-5)


def test_opposite_vectors():
    v1 = (1.0, 0.0)
    v2 = (-1.0, 0.0)
    assert _vector.calculate_angle(v1, v2) == pytest.approx(math.pi, rel=1e-5)


def test_int_vectors():
    # Orthogonal vectors
    v1 = [1, 0]
    v2 = [0, 1]
    assert _vector.calculate_angle(
        v1, v2) == pytest.approx(math.pi/2, rel=1e-5)

    # Opposite vectors
    v1 = [1, 1]
    v2 = [-1, -1]
    assert _vector.calculate_angle(v1, v2) == pytest.approx(math.pi, rel=1e-5)

    # Acute angle
    v1 = [1, 2]
    v2 = [2, 3]
    assert 0 < _vector.calculate_angle(v1, v2) < math.pi/2

    # Obtuse angle
    v1 = [1, 2]
    v2 = [-2, 1]
    assert math.pi/2 < _vector.calculate_angle(v1, v2) < math.pi


def test_float_vectors():
    # Orthogonal vectors
    v1 = [1.5, 0.5]
    v2 = [-0.5, 1.5]
    assert _vector.calculate_angle(
        v1, v2) == pytest.approx(math.pi/2, rel=1e-5)

    # Opposite vectors
    v1 = [1.5, 1.5]
    v2 = [-1.5, -1.5]
    assert _vector.calculate_angle(v1, v2) == pytest.approx(math.pi, rel=1e-5)

    # Acute angle
    v1 = [1.2, 2.3]
    v2 = [2.4, 3.1]
    assert 0 < _vector.calculate_angle(v1, v2) < math.pi/2

    # Obtuse angle
    v1 = [1.2, 2.3]
    v2 = [-2.3, 1.1]
    assert math.pi/2 < _vector.calculate_angle(v1, v2) < math.pi


def test_specific_angle():
    v0 = [0.7027418321943354, 0.9206890990594353]
    v1 = [0.8805969890497817, 0.0048339040196602]

    angle = _vector.calculate_angle(v0, v1)

    assert angle == pytest.approx(0.913362, rel=1e-5)


def test_invalid_argument_types():
    with pytest.raises(TypeError):
        _vector.calculate_angle([1, 1])
        _vector.calculate_angle()
        _vector.calculate_angle([1, 1, 1])
        _vector.calculate_angle([1, 1], [1, 1], [1, 1])
        _vector.calculate_angle(1, 1)
