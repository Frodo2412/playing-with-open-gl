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
#include "OpenGL-basico/utils/gamehud.h"

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

    const square contenedor = square(vector(-0.8, -0.9, 0.0), vector(0.8, -0.9, 0.0), vector(0.8, -0.6, 0.0), vector(-0.8, -0.6, 0.0));
    const auto bricks_texture = texture_loader::load_texture("../assets/bricks_1.jpg");
    const auto some_block = cube(1, vector(0, 0, 0));

    
    gamehud prueba = gamehud();
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
        
        // Limpiar el búfer de color y el búfer de profundidad
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Configurar la proyección ortogonal
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Especifico la proyección: ortogonal.

        // Configurar la matriz de modelo-vista
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        // Dibujar el contenedor del HUD
        Uint32 tiempo = clock::get_total_time();
        prueba.drop_time(tiempo);
        renderer::draw(contenedor, grass_texture);

        // Restaurar la matriz de modelo-vista
        glPopMatrix();

        // Restaurar la matriz de proyección
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        // Dibujar el resto de la escena
        glMatrixMode(GL_MODELVIEW);
        renderer::draw(floor, grass_texture);
        renderer::draw(some_block, bricks_texture);

        float elapsed_time = static_cast<float>(clock::get_ticks());
        
        //MANEJO DE EVENTOS
        while (SDL_PollEvent(&event) )
        {
            switch (event.type)
            {
            case SDL_MOUSEWHEEL:
                    if (event.wheel.y > 0)
                        camera.zoom_in(0.1f * elapsed_time);
                    else
                        camera.zoom_out(0.1f * elapsed_time);
                break;
            case SDL_MOUSEMOTION:
                {
                    float x_offset = static_cast<float>(event.motion.xrel) * elapsed_time;
                    float y_offset = -static_cast<float>(event.motion.yrel) * elapsed_time;
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
