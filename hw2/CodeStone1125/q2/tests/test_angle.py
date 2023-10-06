import math
import pytest
import _vector as v
# Define test cases for the angle function
class TestAngleFunction:
    def test_zero_length_vector(self):
        # Create two zero-length vectors
        vector1 = v.Vector2D(0, 0)
        vector2 = v.Vector2D(0, 0)

        # Use pytest.raises to check if a specific exception is raised when angle is calculated
        with pytest.raises(v.ZeroLengthVectorException):  # Replace 'Exception' with the actual exception type that angle() raises
            v.angle(vector1, vector2)

    def test_zero_angle(self):
        vector1 = v.Vector2D(1, 0)
        vector2 = v.Vector2D(1, 0)
        result = v.angle(vector1, vector2)
        assert result == 0

    def test_right_angle(self):
        vector1 = v.Vector2D(1, 0)
        vector2 = v.Vector2D(0, 1)
        result = v.angle(vector1, vector2)
        assert result == 90

    def test_other_angle(self):
        vector1 = v.Vector2D(1, 1)
        vector2 = v.Vector2D(1, 0)
        result = v.angle(vector1, vector2)
        assert math.isclose(result, 45, rel_tol=1e-9)  # Using math.isclose with a tolerance

