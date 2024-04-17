#include "camera_handler.h"
#include "first_person_camera.h"
#include "top_down_camera.h"
#include "perspective_camera.h"

#include <iostream>

camera_mode camera_handler::mode_ = first;

first_person_camera* camera_handler::first_person_instance_ = new first_person_camera();
top_down_camera* camera_handler::top_down_instance_ = new top_down_camera();
perspective_camera* camera_handler::perspective_instance_ = new perspective_camera();

camera* camera_handler::get_current_camera()
{
    switch (mode_)
    {
    case first: return first_person_instance_;
    case top_down: return top_down_instance_;
    case perspective: return perspective_instance_;
    }
    return nullptr;
}

void camera_handler::toggle_current_camera()
{
    switch (mode_)
    {
    case first:
        std::cout << "CAMERA CHANGED TO ORIGINAL\n";
        mode_ = top_down;
        break;
    case top_down:
        std::cout << "CAMERA CHANGED TO PERSPECTIVE\n";
        mode_ = perspective;
        break;
    case perspective:
        std::cout << "CAMERA CHANGED TO FIRST PERSON\n";
        mode_ = first;
        break;
    }
}
