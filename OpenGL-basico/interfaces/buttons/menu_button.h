#pragma once
#include "button.h"
#include "../../textures/texture_loader.h"

class menu_button : public button
{
private:
    static texture texture_;
public:
    menu_button(char* file_path);
    void on_click() override;
    GLuint get_texture_id() const override;
};
