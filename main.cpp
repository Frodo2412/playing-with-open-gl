#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <conio.h>
#include <GL/glu.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "OpenGL-basico/geometry//vector.h"
#include "OpenGL-basico/geometry/grid.h"
#include "OpenGL-basico/geometry/square.h"
#include "OpenGL-basico/textures/texture.h"
#include "OpenGL-basico/textures/texture_loader.h"
#include "OpenGL-basico/utils/camera.h"
#include "OpenGL-basico/utils/clock.h"
#include "OpenGL-basico/utils/renderer.h"

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
    SDL_Event event;

    auto camera = ::camera(0, 0, 5);

    auto displacement = vector(0, 0, 0);

    const auto grass_texture = texture_loader::load_texture("../assets/grass_1.jpg");
    const auto floor = grid(10, 10, 1, vector(0, 1, 0));

    const auto bricks_texture = texture_loader::load_texture("../assets/bricks_1.jpg");
    const auto some_block = cube(1, vector(0, 0, 0));

    
    //const auto pause_texture = texture_loader::load_texture("../assets/pausa.png");
    //const auto pantallaPausa = square(vector(-320,-240,1), vector(320,-240,1), vector(320,240,1), vector(-320,240,1));
    //estoy teniendo problemas con la ubicación de la pantalla de pausa y que quede del tamaño adecuado.
    // también queda rotada cuando se rota la escena.
    
    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        camera.move(displacement);
        const auto camera_position = camera.get_position();
        const auto camera_direction = camera.get_direction();
        const auto camera_up = camera.get_up();
        gluLookAt(camera_position.get_x(), camera_position.get_y(), camera_position.get_z(),
                  camera_direction.get_x(), camera_direction.get_y(), camera_direction.get_z(),
                  camera_up.get_x(), camera_up.get_y(), camera_up.get_z());
        displacement.reset();

        renderer::draw(floor, grass_texture);
        renderer::draw(some_block, bricks_texture);
        
            //renderer::draw(pantallaPausa, pause_texture);
            // la idea es al pausar que se muestre una imagen con una pantalla de pausa, podría también,
            // desde la pantalla de pausa hacerse todos los settings
            // creo que sería más fácil de esta manera para no tener que hacer dos menús distintos.

        float lapse_time = clock::get_ticks();
        
        //MANEJO DE EVENTOS
        while (SDL_PollEvent(&event) )
        {
            switch (event.type)
            {
            case SDL_MOUSEWHEEL:
                    if (event.wheel.y > 0)
                        camera.zoom_in(0.1f);
                    else
                        camera.zoom_out(0.1f);
                break;
            case SDL_MOUSEMOTION:
                {
                    float x_offset = static_cast<float>(event.motion.xrel) * lapse_time;
                    float y_offset = -static_cast<float>(event.motion.yrel) * lapse_time;
                    std::cout << "Mouse movement: " << x_offset << ", " << y_offset << "\n";
                    camera.rotate(x_offset, y_offset);
                }
                break;
            case SDL_QUIT:
                fin = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                        std::cout << "LEFT\n";
                        displacement.set_x(0.1f * lapse_time);
                    break;
                case SDLK_d:
                        std::cout << "RIGHT\n";
                        displacement.set_x(-0.1f * lapse_time);
                    break;
                case SDLK_w:
                        std::cout << "UP\n";
                        displacement.set_z(0.1f * lapse_time);
                    break;
                case SDLK_s:
                        std::cout << "DOWN\n";
                        displacement.set_z(-0.1f * lapse_time);
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
