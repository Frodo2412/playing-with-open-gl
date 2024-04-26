#include "checkbox.h"
#include  "../../interfaces/settings.h"

auto const settings = settings::get_instance();

GLuint checkbox::get_texture_id() const
{
    if (is_enabled()) return enabled_texture_.get_texture_id();
    return disabled_texture_.get_texture_id();
}

bool facetado_checkbox::is_enabled() const
{
    return settings->facetado_enabled;
}

void facetado_checkbox::on_click()
{
    settings->facetado_enabled = !settings->facetado_enabled;
}

bool wireframe_checkbox::is_enabled() const
{
    return settings->wireframe_enabled;
}

void wireframe_checkbox::on_click()
{
    settings->wireframe_enabled = !settings->wireframe_enabled;
}

bool texturas_checkbox::is_enabled() const
{
    return settings->textures_enabled;
}

void texturas_checkbox::on_click()
{
    settings->textures_enabled = !settings->textures_enabled;
}
