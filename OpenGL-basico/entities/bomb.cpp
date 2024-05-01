#include "bomb.h"

#include "brick_block.h"
#include "metal_block.h"

const bool bomb::is_exploded()
{
    return exploded_;
}

const float bomb::get_timer()
{
    return timer_;
}

void bomb::set_timer(float timer)
{
    timer_ = timer;
}

void bomb::explotar(std::vector<block*>& bloques, std::vector<enemy>& enemies)
{
    exploded_ = true;
    bool continuar = true;
    
    int i_max = rango_horizontal_;
    int k_min = -rango_horizontal_;
    int j_max = rango_vertical_;
    int l_min = -rango_vertical_;

    //ROMPER HORIZONTAL
    for(int i = 0; i <= rango_horizontal_; i++)
    {
        vector3 pos = get_position() + vector3(static_cast<float>(i), 0, 0);
        for(auto& bloque : bloques)
        {
            brick_block* bloque_destructible  = dynamic_cast<brick_block*>(bloque);
            if(bloque_destructible != nullptr  && bloque_destructible->get_posicion().get_x() + 0.5 > pos.get_x() && bloque_destructible->get_posicion().get_x() - 0.5 < pos.get_x() && bloque_destructible->get_posicion().get_z() + 0.5 > pos.get_z() && bloque_destructible->get_posicion().get_z() - 0.5 < pos.get_z())
            {
                bloque_destructible->destroy();
            }else if (bloque_destructible == nullptr) // si no es un bloque destructible --> es no destructible, para la explosión.
            {
                metal_block* bloque_no_destructible  = dynamic_cast<metal_block*>(bloque);
                if(bloque_no_destructible != nullptr  && bloque_no_destructible->get_posicion().get_x() + 0.5 > pos.get_x() && bloque_no_destructible->get_posicion().get_x() - 0.5 < pos.get_x() && bloque_no_destructible->get_posicion().get_z() + 0.5 > pos.get_z() && bloque_no_destructible->get_posicion().get_z() - 0.5 < pos.get_z())
                {
                    i_max = i;
                    continuar = false;
                    break;
                }
            }
        }
        if (!continuar)
            break;
    };
    continuar = true;
    for(int k = -rango_horizontal_; k < 0; k++)
    {
        vector3 pos = get_position() + vector3(static_cast<float>(k), 0, 0);
        for(auto& bloque : bloques)
        {
            brick_block* bloque_destructible  = dynamic_cast<brick_block*>(bloque);
            if(bloque_destructible != nullptr  && bloque_destructible->get_posicion().get_x() + 0.5 > pos.get_x() && bloque_destructible->get_posicion().get_x() - 0.5 < pos.get_x() && bloque_destructible->get_posicion().get_z() + 0.5 > pos.get_z() && bloque_destructible->get_posicion().get_z() - 0.5 < pos.get_z())
            {
                bloque_destructible->destroy();
            }else if (bloque_destructible == nullptr) // si no es un bloque destructible --> es no destructible, para la explosión.
            {
                metal_block* bloque_no_destructible  = dynamic_cast<metal_block*>(bloque);
                if(bloque_no_destructible != nullptr  && bloque_no_destructible->get_posicion().get_x() + 0.5 > pos.get_x() && bloque_no_destructible->get_posicion().get_x() - 0.5 < pos.get_x() && bloque_no_destructible->get_posicion().get_z() + 0.5 > pos.get_z() && bloque_no_destructible->get_posicion().get_z() - 0.5 < pos.get_z())
                {
                    k_min = k;
                    continuar = false;
                    break;
                }
            }
        }
        if (!continuar)
            break;
    };
    continuar = true;
    //ROMPER VERTICAL
    for(int j = 0; j <= rango_vertical_; j++)
    {
        vector3 pos = get_position() + vector3(0, 0, static_cast<float>(j));
        for(auto& bloque : bloques)
        {
            brick_block* bloque_destructible  = dynamic_cast<brick_block*>(bloque);
            if(bloque_destructible != nullptr  && bloque_destructible->get_posicion().get_x() + 0.5 > pos.get_x() && bloque_destructible->get_posicion().get_x() - 0.5 < pos.get_x() && bloque_destructible->get_posicion().get_z() + 0.5 > pos.get_z() && bloque_destructible->get_posicion().get_z() - 0.5 < pos.get_z())
            {
                bloque_destructible->destroy();
            }else if (bloque_destructible == nullptr) // si no es un bloque destructible --> es no destructible, para la explosión.
            {
                metal_block* bloque_no_destructible  = dynamic_cast<metal_block*>(bloque);
                if(bloque_no_destructible != nullptr  && bloque_no_destructible->get_posicion().get_x() + 0.5 > pos.get_x() && bloque_no_destructible->get_posicion().get_x() - 0.5 < pos.get_x() && bloque_no_destructible->get_posicion().get_z() + 0.5 > pos.get_z() && bloque_no_destructible->get_posicion().get_z() - 0.5 < pos.get_z())
                {
                    j_max = j;
                    continuar = false;
                    break;
                }
            }
        }
        if (!continuar)
            break;
    };
    continuar = true;
    for(int l = -rango_vertical_; l < 0; l++)
    {
        vector3 pos = get_position() + vector3(0, 0, static_cast<float>(l));
        for(auto& bloque : bloques)
        {
            brick_block* bloque_destructible  = dynamic_cast<brick_block*>(bloque);
            if(bloque_destructible != nullptr  && bloque_destructible->get_posicion().get_x() + 0.5 > pos.get_x() && bloque_destructible->get_posicion().get_x() - 0.5 < pos.get_x() && bloque_destructible->get_posicion().get_z() + 0.5 > pos.get_z() && bloque_destructible->get_posicion().get_z() - 0.5 < pos.get_z())
            {
                bloque_destructible->destroy();
            }else if (bloque_destructible == nullptr) // si no es un bloque destructible --> es no destructible, para la explosión.
            {
                metal_block* bloque_no_destructible  = dynamic_cast<metal_block*>(bloque);
                if(bloque_no_destructible != nullptr  && bloque_no_destructible->get_posicion().get_x() + 0.5 > pos.get_x() && bloque_no_destructible->get_posicion().get_x() - 0.5 < pos.get_x() && bloque_no_destructible->get_posicion().get_z() + 0.5 > pos.get_z() && bloque_no_destructible->get_posicion().get_z() - 0.5 < pos.get_z())
                {
                    l_min = l;
                    continuar = false;
                    break;
                }
            }
        }
        if (!continuar)
            break;
    };

    //ENEMIGOS
    for(int w = k_min; w <= i_max; w++)
    {
        vector3 pos = get_position() + vector3(static_cast<float>(w), 0, 0);
        for(auto& enemigo : enemies)
        {
            if( enemigo.get_position().get_x() + 0.5 > pos.get_x() && enemigo.get_position().get_x() - 0.5 < pos.get_x() && enemigo.get_position().get_z() + 0.5 > pos.get_z() && enemigo.get_position().get_z() - 0.5 < pos.get_z())
            {
                enemigo.destroy();
            }
        }
    }
    for(int q = l_min; q <= j_max; q++)
    {
        vector3 pos = get_position() + vector3(0, 0, static_cast<float>(q));
        for(auto& enemigo : enemies)
        {
            if( enemigo.get_position().get_x() + 0.5 > pos.get_x() && enemigo.get_position().get_x() - 0.5 < pos.get_x() && enemigo.get_position().get_z() + 0.5 > pos.get_z() && enemigo.get_position().get_z() - 0.5 < pos.get_z())
            {
                enemigo.destroy();
            }
        }
    }
};
