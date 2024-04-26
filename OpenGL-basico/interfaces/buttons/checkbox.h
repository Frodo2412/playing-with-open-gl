#pragma once
#include "button.h"
#include "../../textures/texture_loader.h"

class checkbox : public button
{
    texture enabled_texture_, disabled_texture_;

protected:
    explicit checkbox(const vector2& top_left, const vector2& bottom_right): button(top_left, bottom_right),
                                                                             enabled_texture_(
                                                                                 texture_loader::load_texture(
                                                                                     "../assets/textures/settings/enabled.jpg")),
                                                                             disabled_texture_(
                                                                                 texture_loader::load_texture(
                                                                                     "../assets/textures/settings/disabled.jpg"))
    {
    }

    checkbox(): enabled_texture_(texture_loader::load_texture("../assets/textures/settings/enabled.jpg")),
                disabled_texture_(texture_loader::load_texture("../assets/textures/settings/disabled.jpg"))
    {
    }

    virtual bool is_enabled() const = 0;

public:
    GLuint get_texture_id() const override;
};

class facetado_checkbox final : public checkbox
{
protected:
    bool is_enabled() const override;

public:
    explicit facetado_checkbox(const vector2& top_left, const vector2& bottom_right): checkbox(top_left, bottom_right)
    {
    }

    facetado_checkbox() = default;

    void on_click() override;
};

class wireframe_checkbox final : public checkbox
{
protected:
    bool is_enabled() const override;

public:
    explicit wireframe_checkbox(const vector2& top_left, const vector2& bottom_right): checkbox(top_left, bottom_right)
    {
    }

    wireframe_checkbox() = default;

    void on_click() override;
};

class texturas_checkbox final : public checkbox
{
protected:
    bool is_enabled() const override;

public:
    explicit texturas_checkbox(const vector2& top_left, const vector2& bottom_right): checkbox(top_left, bottom_right)
    {
    }

    texturas_checkbox() = default;
    void on_click() override;
};
