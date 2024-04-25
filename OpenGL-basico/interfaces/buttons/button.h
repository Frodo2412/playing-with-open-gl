#pragma once
#include "../../textures/texture.h"
#include "../../geometry/vector2.h"

class button
{
    vector2 top_left_, bottom_right_;

protected:
    explicit button(const vector2& top_left, const vector2& bottom_right): top_left_(top_left),
                                                                           bottom_right_(bottom_right)
    {
    }

public:
    virtual ~button() = default;

    button(): top_left_(vector2()), bottom_right_(vector2())
    {
    }

    bool is_inside(int x, int y) const;

    float get_top_left_x() const;
    float get_top_left_y() const;

    float get_bottom_right_x() const;
    float get_bottom_right_y() const;

    virtual GLuint get_texture_id() const
    =
    0;
};
