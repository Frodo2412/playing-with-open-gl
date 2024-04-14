#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <conio.h>
#include <GL/glu.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "OpenGL-basico/geometry/Triangle.h"
#include "OpenGL-basico/geometry//vector.h"
#include "OpenGL-basico/geometry/grid.h"
#include "OpenGL-basico/textures/texture.h"
#include "OpenGL-basico/textures/texture_loader.h"
#include "OpenGL-basico/utils/renderer.h"

enum zoom
{
    in,
    out
};

void zoom(vector& camera, const zoom zoom)
{
    switch (zoom)
    {
    case in:
        std::cout << "Zooming in!\n";
        camera.set_z(camera.get_z() - 0.1f);
        break;
    case out:
        std::cout << "Zooming out!\n";
        camera.set_z(camera.get_z() + 0.1f);
    }
}

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
    bool rotate = false;

    SDL_Event event;

    auto camera = vector(0, 0, 5);
    auto main_triangle = triangle(vector(1, -1, 0), vector(-1, -1, 0), vector(0, 1, 0));

    float degrees = 0;
    auto displacement = vector(0, 0, 0);

    const auto grass_texture = texture_loader::load_texture("../assets/grass_1.jpg");
    const auto floor = grid(10, 10, 1, vector(0, 1, 0));

    const auto bricks_texture = texture_loader::load_texture("../assets/bricks_1.jpg");
    const auto some_block = cube(1, vector(0, 0, 0));

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(camera.get_x(), camera.get_y(), camera.get_z(), 0, 0, 0, 0, 1, 0);

        if (rotate)
        {
            degrees = degrees + 0.5f;
        }
        glRotatef(degrees, 0.0, 1.0, 0.0);

        main_triangle.move(displacement);
        displacement.set_x(0);
        displacement.set_y(0);

        renderer::draw(floor, grass_texture);
        renderer::draw(some_block, bricks_texture);

        //MANEJO DE EVENTOS
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                rotate = true;
                std::cout << "ROT\n";
                break;
            case SDL_MOUSEBUTTONUP:
                rotate = false;
                break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y > 0)
                {
                    zoom(camera, in);
                }
                else
                {
                    zoom(camera, out);
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
                    displacement.set_x(-0.1f);
                    break;
                case SDLK_d:
                    std::cout << "RIGHT\n";
                    displacement.set_x(0.1f);
                    break;
                case SDLK_w:
                    std::cout << "UP\n";
                    displacement.set_y(0.1f);
                    break;
                case SDLK_s:
                    std::cout << "DOWN\n";
                    displacement.set_y(-0.1f);
                    break;
                default: break;
                }
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
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
