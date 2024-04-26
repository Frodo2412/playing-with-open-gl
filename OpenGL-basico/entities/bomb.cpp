#include "bomb.h"

#include "brick_block.h"


void bomb::explotar(std::vector<block*>& bloques)
{
    bool continuar = true;
    for(int i = 0; i < rango_horizontal_; i++)
    {
        vector3 pos = get_position() + vector3(static_cast<float>(i), 0, 0);
        for(auto& bloque : bloques)
        {
            brick_block* bloque_destructible  = dynamic_cast<brick_block*>(bloque);
            if(bloque_destructible != nullptr && bloque_destructible->get_posicion().get_x() == pos.get_x() && bloque_destructible->get_posicion().get_z() == pos.get_z())
            {
                bloque_destructible->destroy();
            }else if (bloque_destructible == nullptr) // si no es un bloque destructible --> es no destructible, para la explosión.
            {
                continuar = false;
                break;
            }
        }
        if (!continuar)
        {
            break;
        }
    };
};