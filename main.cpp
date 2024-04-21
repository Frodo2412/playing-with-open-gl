#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <conio.h>
#include <GL/glu.h>

#include "OpenGL-basico/entities/player.h"
#include "OpenGL-basico/entities/block.h"
#include "OpenGL-basico/entities/wall.h"
#include "OpenGL-basico/geometry/vector3.h"
#include "OpenGL-basico/geometry/grid.h"
#include "OpenGL-basico/textures/texture.h"
#include "OpenGL-basico/textures/texture_loader.h"
#include "OpenGL-basico/utils/clock.h"
#include "OpenGL-basico/utils/renderer.h"
#include "OpenGL-basico/scene/scene.h"
#include "OpenGL-basico/graphics/gamehud.h"
#include "OpenGL-basico/graphics/number.h"


int main(int argc, char* argv[])
{
    //INICIALIZACION
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "No se pudo iniciar SDL: " << SDL_GetError() << '\n';
        exit(1);
    }

    SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(win);

    glMatrixMode(GL_PROJECTION);

    constexpr float color = 0;
    glClearColor(color, color, color, 1);

    gluPerspective(45, 640 / 480.f, 0.1, 100);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

    bool fin = false;
    clock::init();
    number::init();
    gamehud::init();
    SDL_Event event;

    auto displacement = vector3(0, 0, 0);

    const auto grass_texture = texture_loader::load_texture("../assets/textures/grass_1.jpg");
    const auto floor = grid(10, 10, 1, vector3(0, 1, 0));

    const auto bricks_texture = texture_loader::load_texture("../assets/textures/bricks_1.jpg");
    std::vector<block> bloques;
    bloques.push_back(block(vector3(0.5, -0.5, 0)));
    bloques.push_back(block(vector3(1.5, -0.5, 0)));
    std::vector<wall> paredes;
    paredes.push_back(wall(vector3(2.5,-0.5,0)));
    paredes.push_back(wall(vector3(1.5,-0.5,1)));

    auto bomberman = player();
    auto current_scene = scene(&bomberman, vector3(0, 0, -5));
    
    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // Configurar la proyección ortogonal
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Especifico la proyección: ortogonal.

        // Configurar la matriz de modelo-vista
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        
        glColor3f(1.0f, 1.0f, 1.0f); 
        // Dibujar el contenedor del HUD
        Uint32 tiempo = clock::get_total_time();
        gamehud::draw_time(tiempo); 

        // Restaurar la matriz de modelo-vista
        glPopMatrix();

        // Restaurar la matriz de proyección
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        // Dibujar el resto de la escena
        glMatrixMode(GL_MODELVIEW);
        
        current_scene.move_player(displacement);
        displacement.reset();

        current_scene.render_scene();
        renderer::draw(floor, grass_texture);
        for(auto bloque: bloques){
            bloque.draw_block();
        }
        for(auto pared: paredes){
            pared.draw_wall();
        }
        renderer::draw(bomberman);

        float elapsed_time = static_cast<float>(clock::get_ticks());

        //MANEJO DE EVENTOS
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEWHEEL:
                // if (event.wheel.y > 0) camera_handler::get_current_camera()->zoom_in(0.1f);
                // else camera_handler::get_current_camera()->zoom_out(0.1f);
                break;
            case SDL_MOUSEMOTION:
                {
                    const float x_offset = static_cast<float>(event.motion.xrel) * elapsed_time;
                    const float y_offset = -static_cast<float>(event.motion.yrel) * elapsed_time;
                    std::cout << "Mouse movement: " << x_offset << ", " << y_offset << "\n";
                    current_scene.rotate_camera(x_offset, y_offset);
                    break;
                }
            case SDL_QUIT:
                fin = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    std::cout << "LEFT\n";
                    displacement.set_x(0.1f * elapsed_time);
                    break;
                case SDLK_d:
                    std::cout << "RIGHT\n";
                    displacement.set_x(-0.1f * elapsed_time);
                    break;
                case SDLK_w:
                    std::cout << "UP\n";
                    displacement.set_z(0.1f * elapsed_time);
                    break;
                case SDLK_s:
                    std::cout << "DOWN\n";
                    displacement.set_z(-0.1f * elapsed_time);
                    break;
                case SDLK_v:
                    current_scene.toggle_camera();
                    break;
                case SDLK_p:
                    std::cout << "PAUSE\n";
                    clock::toggle_pause();
                    break;
                default: break;
                }
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    fin = true;
                    break;
                default: break;
                }
            default: break;
            }
        }
        //FIN MANEJO DE EVENTOS
        SDL_GL_SwapWindow(win);
    }
    while (!fin);
    //FIN LOOP PRINCIPAL
    // LIMPIEZA
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
