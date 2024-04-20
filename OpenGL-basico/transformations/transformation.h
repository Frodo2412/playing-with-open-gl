#pragma once
#include "../geometry/vector3.h"

class transformation
{
    float matrix_[4][4];

protected:
    explicit transformation(float matrix[4][4])
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                matrix_[i][j] = matrix[i][j];
    }

public:
    vector3 transform(const vector3& v) const;
};
