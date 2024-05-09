#pragma once
#include "scene.h"

class level final : public scene
{
    explicit level(const vector3& initial_player_position): scene(initial_player_position)
    {
    }

public:
    static level level1();
};
