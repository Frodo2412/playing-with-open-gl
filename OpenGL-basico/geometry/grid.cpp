#include "grid.h"

int grid::get_rows() const
{
    return rows_;
}

int grid::get_columns() const
{
    return columns_;
}

float grid::get_cell_size() const
{
    return cell_size_;
}

vector grid::get_normal() const
{
    return normal_;
}
