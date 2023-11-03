#ifndef TILEHELPER_H
#define TILEHELPER_H

#include <cstddef>
#include <vector>
#include "matrix.h"

using namespace std;

class TileHelper {
public:
    Matrix padMat(size_t, const Matrix&);
};

#endif 