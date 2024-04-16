#pragma once
#include "vector3.h"

class grid
{
    int rows_, columns_;
    float cell_size_;

    vector3 normal_;

public:
    explicit grid(const int rows, const int columns, const float cell_size, const vector3& normal):
        rows_(rows), columns_(columns),
        cell_size_(cell_size), normal_(normal)
    {
    }

    int get_rows() const;
    int get_columns() const;

    float get_cell_size() const;

    vector3 get_normal() const;
};
