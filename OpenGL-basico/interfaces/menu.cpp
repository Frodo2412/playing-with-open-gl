#include "menu.h"
menu* menu::instance_ = nullptr;

menu::menu()
{
    started_ = false;
    victory_ = false;
}

menu* menu::get_instance()
{
    if (instance_ == nullptr)
    {
        instance_ = new menu();
    }
    return instance_;
}

void menu::set_started(bool started)
{
    started_ = started;
}

bool menu::get_started()
{
    return started_;
}

GLuint menu::get_background_texture_id() const
{
    return background_image_.get_texture_id();
}

void menu::handle_event(int x, int y)
{
    if (victory_)
    {
        victory_ = false;
        started_ = false;
    } else  
        started_ = true;
}

void menu::set_victory(bool victory)
{
    victory_ = victory;
}

bool menu::get_victory()
{
    return victory_;
}

GLuint menu::get_victory_texture_id() const
{
    return victory_image_.get_texture_id();
}