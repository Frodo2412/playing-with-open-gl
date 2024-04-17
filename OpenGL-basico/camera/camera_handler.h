#pragma once
#include "first_person_camera.h"
#include "perspective_camera.h"
#include "top_down_camera.h"

enum camera_mode
{
    first,
    top_down,
    perspective
};

class camera_handler
{
    static camera_mode mode_;

    static first_person_camera* first_person_instance_;
    static top_down_camera* top_down_instance_;
    static perspective_camera* perspective_instance_;

public:
    static camera* get_current_camera();
    static void toggle_current_camera();
    static camera_mode get_mode();
};
