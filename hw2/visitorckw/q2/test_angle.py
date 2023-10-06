from _vector import calculate_angle
import math

def test_calculate_angle():
    assert math.isclose(calculate_angle(1, 0, 0, 1), math.pi / 2, rel_tol=1e-9)
    assert math.isclose(calculate_angle(1, 0, -1, 0), math.pi, rel_tol=1e-9)
    assert math.isclose(calculate_angle(1, 0, 1, 0), 0.0, rel_tol=1e-9)

if __name__ == "__main__":
    test_calculate_angle()
