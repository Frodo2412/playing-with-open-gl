
#pragma once
#include "../geometry/vector2.h"
#include "../textures/texture_loader.h"


enum light_colors
{
    day,
    night,
    red,
    green,
    blue
};

enum game_velocity
{
    slow,
    normal,
    fast
};

class settings
{
private:
    game_velocity game_velocity_ = game_velocity::normal;
    bool wireframe_enabled_ = false;
    bool textures_enabled_ = true;
    bool facetado_enabled_ = false;
    light_colors light_color_;
    static settings* instance_;
    float winHeigth_;
    float winWidth_;
    vector2 enabled_screen_coords[5];
    settings();
    //TEXTURAS DEL SETTINGS
    texture ajustes_texture = texture_loader::load_texture("../assets/textures/settings/ajustes.jpg");
    texture slow_settings_texture = texture_loader::load_texture("../assets/textures/settings/slow.jpg");
    texture normal_settings_texture = texture_loader::load_texture("../assets/textures/settings/normal.jpg");
    texture fast_settings_texture = texture_loader::load_texture("../assets/textures/settings/fast.jpg");
    texture enabled_texture = texture_loader::load_texture("../assets/textures/settings/enabled.jpg");
    texture disabled_texture = texture_loader::load_texture("../assets/textures/settings/disabled.jpg");
    texture day_settings_texture = texture_loader::load_texture("../assets/textures/settings/dia.jpg");
    texture night_settings_texture = texture_loader::load_texture("../assets/textures/settings/noche.jpg");
    texture red_settings_texture = texture_loader::load_texture("../assets/textures/settings/rojo.jpg");
    texture green_settings_texture = texture_loader::load_texture("../assets/textures/settings/verde.jpg");
    texture blue_settings_texture = texture_loader::load_texture("../assets/textures/settings/azul.jpg");
public:
    static settings* get_instance();
    void set_game_velocity(game_velocity game_velocity);
    game_velocity get_game_velocity();
    void set_wireframe_enabled(bool wireframe);
    bool get_wireframe_enabled();
    void set_light_color(light_colors color);
    light_colors get_light_color();
    float get_winHeigth();
    float get_winWidth();
    void set_winHeigth(float winHeigth);
    void set_winWidth(float winWidth);
    bool get_textures_enabled();
    void set_textures_enabled(bool textures_enabled);
    bool get_facetado_enabled();
    void set_facetado_enabled(bool facetado_enabled);
    void event_handler(float x, float y);
    void set_enabled_screen_coords(int index, vector2 vector);
    texture get_ajustes_texture();
    texture get_slow_settings_texture();
    texture get_normal_settings_texture();
    texture get_fast_settings_texture();
    texture get_enabled_texture();
    texture get_disabled_texture();
    texture get_day_settings_texture();
    texture get_night_settings_texture();
    texture get_red_settings_texture();
    texture get_green_settings_texture();
    texture get_blue_settings_texture();
    ~settings();
};