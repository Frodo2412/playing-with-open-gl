#pragma once
#include "../geometry/vector.h"

enum CameraMode
{
    first,
    original,
    perspective
};

class camera
{
    vector position_, direction_, up_;
    CameraMode mode_;
    bool move_camera_first_;
    float perspective_zoom_;

public:
    explicit camera(const vector& position, const vector& direction, const vector& up)
        : position_(position), direction_(direction), up_(up)
    {
        mode_ = CameraMode::first;
        move_camera_first_ = false;
        perspective_zoom_ = 0;
    }

    explicit camera(const float x, const float y, const float z)
        : position_(vector(x, y, z)), direction_(vector(0, 0, 0)), up_(vector(0, 1, 0))
    {
        mode_ = CameraMode::first;
        move_camera_first_ = false;
        perspective_zoom_ = 0;
    }

    vector get_position() const;
    vector get_direction() const;
    vector get_up() const;
    CameraMode get_mode();
    bool get_move_camera_first();
    float get_perspective_zoom();

    void set_position(vector pos);

    void set_direction(vector dir);

    void set_up(vector up);
    
    void set_mode(CameraMode mode);

    void set_move_camera_first(bool move_camera_first);
    void set_perspective_zoom(float perspective_zoom);

    void move(const vector& displacement);

    void zoom_in(float amount);
    void zoom_out(float amount);
    
    void rotate(float x_offset, float y_offset);
    
    void refresh(vector bomber_man);
    
};
