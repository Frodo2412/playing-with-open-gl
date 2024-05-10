#include "grid.h"

int grid::get_rows() const
{
    return rows_;
}

int grid::get_columns() const
{
    return columns_;
}

float grid::get_top() const
{
    return top_;
}

float grid::get_left() const
{
    return left_;
}

float grid::get_right() const
{
    return right_;
}

float grid::get_bottom() const
{
    return bottom_;
}

float grid::get_cell_size() const
{
    return cell_size_;
}

vector3 grid::get_normal() const
{
    return normal_;
}
