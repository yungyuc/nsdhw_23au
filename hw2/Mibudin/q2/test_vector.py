import math

import _vector


class TestRadBetweenVec2d:
    def test_zero_dimensional_vector(self) -> None:
        try:
            _vector.rad_between_vec2d([], [])
        except TypeError as err:
            print(
                "Vectors passed into `rad_between_vec2d` should have and only "
                "have 2 elements, which limitation is already hard-coded in "
                "the original C++ implementation code."
            )
            print(err)
    
    def test_zero_length_vector(self) -> None:
        assert math.isnan(_vector.rad_between_vec2d([0, 0], [1, 1]))

    def test_zero_angle(self) -> None:
        assert math.isclose(_vector.rad_between_vec2d([1, 1], [2, 2]), 0)

    def test_right_angle(self) -> None:
        assert math.isclose(
            _vector.rad_between_vec2d([1, 1], [-1, 1]), math.pi / 2)

    def test_other_angle(self) -> None:
        assert math.isclose(_vector.rad_between_vec2d([1, 1], [-1, -1]), math.pi)
