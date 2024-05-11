#pragma once
#include <exception>

class next_level_exception final : public std::exception
{
public:
    const char* what() const override;
};
