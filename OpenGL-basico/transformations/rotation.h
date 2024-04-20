#pragma once
#include "transformation.h"

class rotation final : public transformation
{
public:
    explicit rotation(float angle, vector3 axis): transformation({})
    {
    }
};
