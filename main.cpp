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

    auto bomber_man = vector(0, 0, 5);
    auto camera = ::camera(0, 0, 5);

    const auto grass_texture = texture_loader::load_texture("../assets/grass_1.jpg");
    const auto floor = grid(10, 10, 1, vector(0, 1, 0));

    const auto bricks_texture = texture_loader::load_texture("../assets/bricks_1.jpg");
    const auto some_block = cube(1, vector(0, 0, 0));

    SDL_SetWindowGrab(win, SDL_TRUE);
    SDL_ShowCursor(SDL_TRUE);//SDL_FALSE PARA OCULTAR MOUSE
    
    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        camera.refresh(bomber_man);
        gluLookAt(camera.get_position().get_x(), camera.get_position().get_y(), camera.get_position().get_z(),
              camera.get_direction().get_x(), camera.get_direction().get_y(), camera.get_direction().get_z(),
              camera.get_up().get_x(), camera.get_up().get_y(), camera.get_up().get_z());
        renderer::draw(floor, grass_texture);
        renderer::draw(some_block, bricks_texture);

        //BOMBERMAN MOMENTANEO
        glPointSize(20);
        glBegin(GL_POINTS);
            glColor3f(1,0,0);
            glVertex3f(bomber_man.get_x(), bomber_man.get_y(), bomber_man.get_z());
        glEnd();
        
        //MANEJO DE EVENTOS
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEWHEEL:
                if (event.wheel.y > 0) camera.zoom_in(0.1f);
                if ((event.wheel.y>0 && camera.get_perspective_zoom() < 2) || (event.wheel.y<0 && camera.get_perspective_zoom() > -5))
                {
                    camera.set_perspective_zoom(camera.get_perspective_zoom() + event.wheel.y * 0.20f);
                }
                else camera.zoom_out(0.1f);
                break;
            case SDL_MOUSEMOTION:
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        float x_offset = static_cast<float>(event.motion.xrel);
                        float y_offset = -static_cast<float>(event.motion.yrel);
                        std::cout << "Mouse movement: " << x_offset << ", " << y_offset << "\n";
                        camera.rotate(x_offset, y_offset);
                        camera.set_move_camera_first(true);
                    } else
                    {
                        camera.set_move_camera_first(false);
                    }
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
                    bomber_man.set_x(bomber_man.get_x() - 0.1f);
                    break;
                case SDLK_d:
                    std::cout << "RIGHT\n";
                    bomber_man.set_x(bomber_man.get_x() + 0.1f);
                    break;
                case SDLK_w:
                    std::cout << "UP\n";
                    bomber_man.set_z(bomber_man.get_z() - 0.1f);
                    break;
                case SDLK_s:
                    std::cout << "DOWN\n";
                    bomber_man.set_z(bomber_man.get_z() + 0.1f);
                    break;
                case SDLK_v:
                    switch (camera.get_mode())
                    {
                        case CameraMode::first:
                            std::cout << "CAMERA CHANGED TO ORIGINAL\n";
                            camera.set_mode(CameraMode::original);
                            break;
                        case CameraMode::original:
                            std::cout << "CAMERA CHANGED TO PERSPECTIVE\n";
                            camera.set_mode(CameraMode::perspective);
                            break;
                        case CameraMode::perspective:
                            std::cout << "CAMERA CHANGED TO FIRST PERSON\n";
                            camera.set_mode(CameraMode::first);
                            break;
                    }
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
