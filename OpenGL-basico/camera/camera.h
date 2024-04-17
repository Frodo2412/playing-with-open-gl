#pragma once
#include "../geometry/vector3.h"

class perspective_camera;
class top_down_camera;
class first_person_camera;

enum camera_mode
{
    first,
    top_down,
    perspective
};

class camera
{
protected:
    vector3 position_, direction_, up_;
    ~camera();

public:
    vector3 get_position() const;
    vector3 get_direction() const;
    vector3 get_up() const;

    virtual void move(const vector3& displacement) = 0;
    virtual void rotate(float x_offset, float y_offset) = 0;

    virtual void zoom_in(float amount) = 0;
    virtual void zoom_out(float amount) = 0;
};
