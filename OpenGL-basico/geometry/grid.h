#pragma once
#include <iostream>

#include "vector3.h"

class grid final
{
    int rows_, columns_;
    float cell_size_, top_, left_, right_, bottom_;

    vector3 normal_;

public:
    explicit grid(const int rows, const int columns, const float cell_size, const vector3& normal):
        rows_(rows), columns_(columns),
        cell_size_(cell_size), normal_(normal)
    {
        const auto d = cell_size_ / 2;

        std::cout << "rows: " << rows_ << " columns: " << columns_ << " cell_size: " << cell_size_ << '\n';

        top_ = -static_cast<float>(columns) * d;
        left_ = -static_cast<float>(rows) * d;
        right_ = static_cast<float>(rows) * d;
        bottom_ = static_cast<float>(columns) * d;

        std::cout << "top: " << top_ << " left: " << left_ << " right: " << right_ << " bottom: " << bottom_ << '\n';
    }

    int get_rows() const;
    int get_columns() const;

    float get_top() const;
    float get_left() const;
    float get_right() const;
    float get_bottom() const;

    float get_cell_size() const;

    vector3 get_normal() const;
};
