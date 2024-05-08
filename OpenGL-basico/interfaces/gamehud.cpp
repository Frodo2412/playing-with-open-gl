#include "gamehud.h"
#include "../utils/renderer.h"
#include "number.h"


gamehud* gamehud::instance_ = nullptr;


void gamehud::init()
{
    instance_ = new gamehud();
};

void gamehud::cambiar_numero(const Uint32 valor, square ubicacion)
{
    switch (valor)
    {
    case 0: renderer::draw(ubicacion, number::get_texture_zero());
        break;
    case 1: renderer::draw(ubicacion, number::get_texture_one());
        break;
    case 2: renderer::draw(ubicacion, number::get_texture_two());
        break;
    case 3: renderer::draw(ubicacion, number::get_texture_three());
        break;
    case 4: renderer::draw(ubicacion, number::get_texture_four());
        break;
    case 5: renderer::draw(ubicacion, number::get_texture_five());
        break;
    case 6: renderer::draw(ubicacion, number::get_texture_six());
        break;
    case 7: renderer::draw(ubicacion, number::get_texture_seven());
        break;
    case 8: renderer::draw(ubicacion, number::get_texture_eight());
        break;
    case 9: renderer::draw(ubicacion, number::get_texture_nine());
        break;
    default: break;
    }
}


void gamehud::draw_time(const Uint32 millisecond)
{
    glEnable(GL_TEXTURE_2D);
    Uint32 seconds = millisecond / 1000;
    Uint32 minutes = seconds / 60;
    seconds %= 60;
    minutes %= 60;
    const Uint32 minutes_d = minutes / 10;
    const Uint32 minutes_u = minutes % 10;
    const Uint32 seconds_d = seconds / 10;
    const Uint32 seconds_u = seconds % 10;
    Uint32 score_m = instance_->score_ / 1000;
    Uint32 score_c = (instance_->score_ % 1000) / 100;
    Uint32 score_d = (instance_->score_ % 100) / 10;
    Uint32 score_u = instance_->score_ % 10;

    glDisable(GL_DEPTH_TEST);
    renderer::draw(instance_->contenedor_, number::get_texture_gamehud());
    renderer::draw(instance_->espacio_, number::get_two_dots());

    cambiar_numero(minutes_d, instance_->minutos_decena_);
    cambiar_numero(minutes_u, instance_->minutos_unidades_);
    cambiar_numero(seconds_d, instance_->segundos_decena_);
    cambiar_numero(seconds_u, instance_->segundos_unidades_);
    
    cambiar_numero(score_m, instance_->score_miles_);
    cambiar_numero(score_c, instance_->score_cientos_);
    cambiar_numero(score_d, instance_->score_decenas_);
    cambiar_numero(score_u, instance_->score_unidades_);

    // dibujo los detalles
    renderer::draw(instance_->tiempo_, number::get_texture_time());

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
}

void gamehud::update_points(Uint32 points)
{
    instance_->score_ += points;
};
