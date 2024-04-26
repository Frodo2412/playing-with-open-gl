#include "button.h"

#include <iostream>
#include "../settings.h"

auto const settings = settings::get_instance();

bool button::is_inside(const int x, const int y) const
{
    // Restamos la mitad de la ventana para que el origen sea el centro
    // Esto hay que hacerlo porque los botones se dibujan en perspectiva ortogonal
    const auto float_x = static_cast<float>(x - settings->window_width / 2);
    const auto float_y = static_cast<float>(y - settings->window_height / 2);

    std::cout << "Checking click inside button\n" << "x: " << float_x << ", y: " << y << '\n'
        << "Top left: " << top_left_.get_x() << ", " << top_left_.get_y() << '\n'
        << "Bottom right: " << bottom_right_.get_x() << ", " << bottom_right_.get_y() << '\n';

    
    const auto horizontal = float_x >= top_left_.get_x() && float_x <= bottom_right_.get_x();
    const auto vertical = float_y >= top_left_.get_y() && float_y <= bottom_right_.get_y();

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
