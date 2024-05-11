#include "menu.h"
menu* instance = nullptr;

menu::menu()
{
    background_image_ = texture_loader::load_texture("../assets/textures/menu/menu.jpg");
    start_ = new menu_button("../assets/textures/menu/start.jpg");
    settings_ = new menu_button("../assets/textures/menu/settings.jpg");
}

menu* menu::get_instance()
{
    if (instance == nullptr)
    {
        instance = new menu();
    }
    return instance;
}
