#pragma once
#include "entity.h"
#include "../textures/texture_manager.h"

class pedestal : public entity
{
    bool is_level_completed_;
public:
    explicit pedestal(const vector3& position): entity("../assets/models/Postament.obj",
                                                     texture_manager::postament_texture(), 1,
                                                     position),  is_level_completed_(false)
    {
    }
    
    bool get_is_level_completed();
    void level_completed();
    void handle_collision(game_object* other) override;
    aabb get_bounding_box() const override;
};
