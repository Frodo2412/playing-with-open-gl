#include "menu_button.h"

menu_button::menu_button(char* file_path): button(vector2(0, 0), vector2(0, 0))
{
    texture_ = texture_loader::load_texture(file_path);
}

GLuint menu_button::get_texture_id() const
{
    return texture_.get_texture_id();
}

void menu_button::on_click()
{
    // Do something
}
