#pragma once
#include "../textures/texture.h"
#include <array>
#include "buttons/menu_button.h"
#include "../textures/texture_loader.h"

class menu
{
private:
    menu* instance = nullptr;
    menu();
    static texture background_image_;
    menu_button* start_;
    menu_button* settings_;
public:
    menu* get_instance();
    void handle_click(int x, int y);
    GLuint get_background_texture_id() const;
    std::array<button*, 5> get_buttons();
};
