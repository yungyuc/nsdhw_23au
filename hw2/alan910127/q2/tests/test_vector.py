import _vector
import math

REL_TOL = 1e-9


def test_zero_vector_first():
    angle = _vector.calculate_angle((0, 0), (1, 1))

    assert math.isnan(angle)


def test_zero_vector_second():
    angle = _vector.calculate_angle((1, 1), (0, 0))

    assert math.isnan(angle)


def test_zero_vector_both():
    angle = _vector.calculate_angle((0, 0), (0, 0))

    assert math.isnan(angle)


def test_right_angle():
    angle = _vector.calculate_angle((1, 0), (0, 1))

    assert math.isclose(angle, math.pi / 2, rel_tol=REL_TOL)


def test_right_angle_reverse():
    angle = _vector.calculate_angle((0, 1), (1, 0))

    assert math.isclose(angle, math.pi / 2, rel_tol=REL_TOL)


def test_60_degree():
    angle = _vector.calculate_angle((1, 0), (1, 3**0.5))

    assert math.isclose(angle, math.pi / 3, rel_tol=REL_TOL)


def test_45_degree():
    angle = _vector.calculate_angle((1, 0), (1, 1))

    assert math.isclose(angle, math.pi / 4, rel_tol=REL_TOL)


def test_30_degree():
    angle = _vector.calculate_angle((1, 0), (3**0.5, 1))

    assert math.isclose(angle, math.pi / 6, rel_tol=REL_TOL)


def test_no_angle():
    angle = _vector.calculate_angle((1, 0), (2, 0))

    assert math.isclose(angle, 0, rel_tol=REL_TOL)
