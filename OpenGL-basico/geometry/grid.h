#pragma once
#include "vertex.h"

class grid
{
    int rows_, columns_;
    float cell_size_;

    vertex normal_;

public:
    explicit grid(const int rows, const int columns, const float cell_size, const vertex& normal):
        rows_(rows), columns_(columns),
        cell_size_(cell_size), normal_(normal)
    {
    }

    int get_rows() const;
    int get_columns() const;

    float get_cell_size() const;

    vertex get_normal() const;
};
