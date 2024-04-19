#include "gamehud.h"
#include "../utils/renderer.h"
#include "number.h"

 gamehud::gamehud(){};

void gamehud::cambiar_numero(Uint32 valor, square ubicacion) {
    switch (valor) {
    case 0: renderer::draw(ubicacion, number::get_texture_zero()); break;
    case 1: renderer::draw(ubicacion, number::get_texture_one()); break;
    case 2: renderer::draw(ubicacion, number::get_texture_two()); break;
    case 3: renderer::draw(ubicacion, number::get_texture_three()); break;
    case 4: renderer::draw(ubicacion, number::get_texture_four()); break;
    case 5: renderer::draw(ubicacion, number::get_texture_five()); break;
    case 6: renderer::draw(ubicacion, number::get_texture_six()); break;
    case 7: renderer::draw(ubicacion, number::get_texture_seven()); break;
    case 8: renderer::draw(ubicacion, number::get_texture_eight()); break;
    case 9: renderer::draw(ubicacion, number::get_texture_nine()); break;
    default: std::cout << "error " << "\n"; break;
    }
}


void gamehud::drop_time(Uint32 milisecond)
{
    Uint32 seconds = (milisecond / 1000);
    Uint32 minutes = (seconds / 60);
    seconds %= 60;
    minutes %= 60;
    Uint32 minutes_d = (minutes / 10);
    Uint32 minutes_u = minutes % 10;
    Uint32 seconds_d = (seconds / 10);
    Uint32 seconds_u = (seconds % 10);

    renderer::draw(espacio_, number::get_two_dots());

    gamehud::cambiar_numero(minutes_d, minutos_decena_);
    gamehud::cambiar_numero(minutes_u, minutos_unidades_);
    gamehud::cambiar_numero(seconds_d, segundos_decena_);
    gamehud::cambiar_numero(seconds_u, segundos_unidades_);

    // dibujo los detalles
    renderer::draw(tiempo_, number::get_texture_time());
    renderer::draw(contenedor_, number::get_texture_gamehud());

}