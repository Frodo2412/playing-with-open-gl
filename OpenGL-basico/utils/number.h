#pragma once
#include "../textures/texture_loader.h"

class number
{
    texture texture_;

    static number* one_instance_;
    static number* two_instance_;
    static number* three_instance_;
    static number* four_instance_;
    static number* five_instance_;
    static number* six_instance_;
    static number* seven_instance_;
    static number* eight_instance_;
    static number* nine_instance_;
    static number* zero_instance_;

    explicit number(const char* path) : texture_(texture_loader::load_texture(path))
    {
    }

public:
    const texture get_texture();

    static number* one();
    static number* two();
    static number* three();
    static number* four();
    static number* five();
    static number* six();
    static number* seven();
    static number* eight();
    static number* nine();
    static number* zero();
};