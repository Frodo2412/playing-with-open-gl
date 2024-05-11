#pragma once
#include <stdexcept>

class game_over_exception final : public std::exception
{
public:
    const char* what() const override;
};
