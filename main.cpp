#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <conio.h>
#include <GL/glu.h>

#include "OpenGL-basico/entities/player.h"
#include "OpenGL-basico/geometry/vector3.h"
#include "OpenGL-basico/geometry/grid.h"
#include "OpenGL-basico/textures/texture.h"
#include "OpenGL-basico/textures/texture_loader.h"
#include "OpenGL-basico/utils/clock.h"
#include "OpenGL-basico/utils/renderer.h"
#include "OpenGL-basico/scene/scene.h"
#include "OpenGL-basico/graphics/gamehud.h"
#include "OpenGL-basico/graphics/number.h"
#include "OpenGL-basico/utils/renderer.h"


int main(int argc, char* argv[])
{
    //INICIALIZACION
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "No se pudo iniciar SDL: " << SDL_GetError() << '\n';
        exit(1);
    }

    int winHeigth = 480;
    int winWidth = 640;
    
    SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       winWidth, winHeigth, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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
    const auto ajustes_texture = texture_loader::load_texture("../assets/textures/settings/ajustes.jpg");
    const auto enabled_texture = texture_loader::load_texture("../assets/textures/settings/enabled.jpg");
    const auto disabled_texture = texture_loader::load_texture("../assets/textures/settings/disabled.jpg");
    const auto bricks_texture = texture_loader::load_texture("../assets/textures/bricks_1.jpg");
    const auto some_block = cube(1, vector3(0, 0, 0));


    auto bomberman = player();
    auto current_scene = scene(&bomberman, vector3(0, 0, -5));
    
    int targetFrameDuration = 1000 / 60;//60 FPS
    
    do
    {
        Uint32 lastFrameTime = SDL_GetTicks();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        if (clock::get_instance()->get_is_paused())
        {
            glMatrixMode(GL_PROJECTION);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(-winWidth/2, winWidth/2, -winHeigth/2, winHeigth/2, -1.0, 1.0);
            settings::get_instance()->set_winHeigth(winHeigth);//ESTO LO PONGO QUE LO ACTUALICE SIEMPRE POR SI DESPUES HACEMOS QUE SE PUEDA CAMBIAR LA RESOLUCION
            settings::get_instance()->set_winWidth(winWidth);
            renderer::draw(settings::get_instance(), current_scene.get_camera()->get_position(), ajustes_texture, enabled_texture, disabled_texture);
            glPopMatrix();
        } else
        {
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
        }

        // Dibujar el resto de la escena
        glMatrixMode(GL_MODELVIEW);
        
        if (settings::get_instance()->get_wireframe_enabled())
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        if(settings::get_instance()->get_textures_enabled())
        {
            glEnable(GL_TEXTURE_2D);
        } else
        {
            glDisable(GL_TEXTURE_2D);
        }

        if(settings::get_instance()->get_facetado_enabled())
        {
            glShadeModel(GL_FLAT);
        } else
        {
            glShadeModel(GL_SMOOTH);
        }
        
        current_scene.move_player(displacement);
        displacement.reset();

        current_scene.render_scene();

        renderer::draw(floor, grass_texture);
        renderer::draw(some_block, bricks_texture);
        renderer::draw(bomberman);
        
        
        Uint32 currentFrameTime = SDL_GetTicks();
        Uint32 deltaTime = currentFrameTime - lastFrameTime;
        std::cout << "deltaTime: " << deltaTime << std::endl;
        /*if (deltaTime < targetFrameDuration)//limita a 60fps maximo
        {
            SDL_Delay(targetFrameDuration-deltaTime); 
        }*/
        if (settings::get_instance()->get_slow_mode())//ARREGLAR DESPEUS
        {
            deltaTime = deltaTime * 2;
        }
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
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    settings::get_instance()->event_handler(event.button.x, -event.button.y); //Y ES NEGATIVO PORQUE ARRIBA ES 0 Y ABAJO ES 480
                    std::cout << "click en: (" << event.button.x << ", " << event.button.y << ")" << std::endl;
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
