#include "transformation.h"

vector3 transformation::transform(const vector3& v) const
{
    const float vec[4] = {v.get_x(), v.get_y(), v.get_z(), 1};
    float result[4] = {0, 0, 0, 0};

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result[i] += matrix_[i][j] * vec[j];

    return vector3(result[0], result[1], result[2]);
}
