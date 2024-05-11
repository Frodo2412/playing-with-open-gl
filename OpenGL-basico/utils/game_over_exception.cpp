#include "game_over_exception.h"

const char* game_over_exception::what() const
{
    return "Game over!";
}
