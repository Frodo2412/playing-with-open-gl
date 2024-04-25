#include "button.h"

bool button::is_inside(const int x, const int y) const
{
    const auto float_x = static_cast<float>(x);
    const auto float_y = static_cast<float>(y);

    const auto horizontal = float_x >= top_left_.get_x() && float_x <= bottom_right_.get_x();
    const auto vertical = float_y >= bottom_right_.get_y() && float_y <= top_left_.get_y();

    return horizontal && vertical;
}

float button::get_top_left_x() const
{
    return top_left_.get_x();
}

float button::get_top_left_y() const
{
    return top_left_.get_y();
}

float button::get_bottom_right_x() const
{
    return bottom_right_.get_x();
}

float button::get_bottom_right_y() const
{
    return bottom_right_.get_y();
}
