#pragma once
#include "vector.h"

class grid
{
    int rows_, columns_;
    float cell_size_;

    vector normal_;

public:
    explicit grid(const int rows, const int columns, const float cell_size, const vector& normal):
        rows_(rows), columns_(columns),
        cell_size_(cell_size), normal_(normal)
    {
    }

    int get_rows() const;
    int get_columns() const;

    float get_cell_size() const;

    vector get_normal() const;
};
