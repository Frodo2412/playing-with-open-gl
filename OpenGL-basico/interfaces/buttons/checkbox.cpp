#include "checkbox.h"
#include "../../utils/settings.h"

GLuint checkbox::get_texture_id() const
{
    if (is_enabled()) return enabled_texture_.get_texture_id();
    return disabled_texture_.get_texture_id();
}

bool facetado_checkbox::is_enabled() const
{
    return settings::get_instance()->get_facetado_enabled();
}

bool wireframe_checkbox::is_enabled() const
{
    return settings::get_instance()->get_wireframe_enabled();
}

bool texturas_checkbox::is_enabled() const
{
    return settings::get_instance()->get_textures_enabled();
}
