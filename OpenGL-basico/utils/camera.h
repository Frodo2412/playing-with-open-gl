#pragma once
#include "../geometry/vector3.h"

enum CameraMode
{
    first,
    original,
    perspective
};

class camera
{
    vector3 position_, direction_, up_;
    CameraMode mode_;
    float perspective_zoom_;

public:
    explicit camera(const vector3& position, const vector3& direction, const vector3& up)
        : position_(position), direction_(direction), up_(up)
    {
        mode_ = CameraMode::first;
        perspective_zoom_ = 0;
    }

    explicit camera(const float x, const float y, const float z)
        : position_(vector3(x, y, z)), direction_(vector3(0, 0, 0)), up_(vector3(0, 1, 0))
    {
        mode_ = CameraMode::first;
        perspective_zoom_ = 0;
    }

    vector3 get_position() const;
    vector3 get_direction() const;
    vector3 get_up() const;
    CameraMode get_mode();
    
    float get_perspective_zoom();
    
    void set_perspective_zoom(float perspective_zoom);

    void move(const vector3& displacement);

    void zoom_in(float amount);
    void zoom_out(float amount);
    
    void rotate(float x_offset, float y_offset);

    void toggle_mode();
    
    void refresh(vector3 bomber_man);
    
};
