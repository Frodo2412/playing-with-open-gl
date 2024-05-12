#pragma once

#include "../textures/texture_loader.h"

class menu
{
private:
    static menu* instance_;
    menu();
    texture background_image_ = texture_loader::load_texture("../assets/textures/menu.jpg");
    texture victory_image_ = texture_loader::load_texture("../assets/textures/victory.jpg");
    bool started_;
    bool victory_;
public:
    static menu* get_instance();
    void set_started(bool started);
    bool get_started();
    GLuint get_background_texture_id() const;
    GLuint get_victory_texture_id() const;
    void handle_event(int x, int y);
    void set_victory(bool victory);
    bool get_victory();
};
