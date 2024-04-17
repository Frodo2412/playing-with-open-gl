
#include "gamehud.h"
#include "renderer.h"
#include "number.h"

 gamehud::gamehud(){};

void gamehud::drop_time(Uint32 milisecond)
{
    Uint32 seconds = (milisecond / 1000);
    Uint32 minutes = (seconds / 60);
    seconds %= 60;
    minutes %= 60;
    Uint32 minutes_d = (minutes / 10);
    Uint32 minutes_u = minutes_d % 10;
    Uint32 seconds_d = (seconds / 10);
    Uint32 seconds_u = (seconds_d % 10);

    const texture prueba = texture_loader::load_texture("../assets/two_dots.png");
    renderer::draw(espacio_, prueba);

    std::cout << minutes_d << minutes_u << ":" << seconds_d << seconds_u <<  " transcurridos." << "\n";
    
    switch (minutes_d) {
    case 0: renderer::draw(minutos_decena_, number::zero()->get_texture()); break;
    case 1:  renderer::draw(minutos_decena_, number::one()->get_texture()); break;
    case 2: renderer::draw(minutos_decena_, number::two()->get_texture()); break;
    case 3: renderer::draw(minutos_decena_, number::three()->get_texture()); break;
    case 4: renderer::draw(minutos_decena_, number::four()->get_texture()); break;
    case 5: renderer::draw(minutos_decena_, number::five()->get_texture()); break;
    case 6: renderer::draw(minutos_decena_, number::six()->get_texture()); break;
    case 7: renderer::draw(minutos_decena_, number::seven()->get_texture()); break;
    case 8: renderer::draw(minutos_decena_, number::eight()->get_texture()); break;
    case 9: renderer::draw(minutos_decena_, number::nine()->get_texture()); break;
    default: std::cout << "error" << "\n"; break;
    }

    switch (minutes_u) {
    case 0: renderer::draw(minutos_unidades_, number::zero()->get_texture()); break;
    case 1: renderer::draw(minutos_unidades_, number::one()->get_texture()); break;
    case 2: renderer::draw(minutos_unidades_, number::two()->get_texture()); break;
    case 3: renderer::draw(minutos_unidades_, number::three()->get_texture()); break;
    case 4: renderer::draw(minutos_unidades_, number::four()->get_texture()); break;
    case 5: renderer::draw(minutos_unidades_, number::five()->get_texture()); break;
    case 6: renderer::draw(minutos_unidades_, number::six()->get_texture()); break;
    case 7: renderer::draw(minutos_unidades_, number::seven()->get_texture()); break;
    case 8: renderer::draw(minutos_unidades_, number::eight()->get_texture()); break;
    case 9: renderer::draw(minutos_unidades_, number::nine()->get_texture()); break;
    default: std::cout << "error" << "\n"; break;
    }
    
    switch (seconds_d) {
    case 0: renderer::draw(segundos_decena_, number::zero()->get_texture()); break;
    case 1: renderer::draw(segundos_decena_, number::one()->get_texture()); break;
    case 2: renderer::draw(segundos_decena_, number::two()->get_texture()); break;
    case 3: renderer::draw(segundos_decena_, number::three()->get_texture()); break;
    case 4: renderer::draw(segundos_decena_, number::four()->get_texture()); break;
    case 5: renderer::draw(segundos_decena_, number::five()->get_texture()); break;
    case 6: renderer::draw(segundos_decena_, number::six()->get_texture()); break;
    case 7: renderer::draw(segundos_decena_, number::seven()->get_texture()); break;
    case 8: renderer::draw(segundos_decena_, number::eight()->get_texture()); break;
    case 9: renderer::draw(segundos_decena_, number::nine()->get_texture()); break;
    default: std::cout << "error" << "\n"; break;
    }

    switch (seconds_u) {
    case 0: renderer::draw(segundos_unidades_, number::zero()->get_texture()); break;
    case 1: renderer::draw(segundos_unidades_, number::one()->get_texture()); break;
    case 2: renderer::draw(segundos_unidades_, number::two()->get_texture()); break;
    case 3: renderer::draw(segundos_unidades_, number::three()->get_texture()); break;
    case 4: renderer::draw(segundos_unidades_, number::four()->get_texture()); break;
    case 5: renderer::draw(segundos_unidades_, number::five()->get_texture()); break;
    case 6: renderer::draw(segundos_unidades_, number::six()->get_texture()); break;
    case 7: renderer::draw(segundos_unidades_, number::seven()->get_texture()); break;
    case 8: renderer::draw(segundos_unidades_, number::eight()->get_texture()); break;
    case 9: renderer::draw(segundos_unidades_, number::nine()->get_texture()); break;
    default: std::cout << "error undidas" << "\n"; break;
    }
}
