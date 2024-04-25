#include "settings.h"

settings* settings::instance_ = nullptr;

settings* settings::get_instance()
{
    if (instance_ == nullptr)
    {
        instance_ = new settings();
    }
    return instance_;
}
