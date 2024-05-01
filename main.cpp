#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <conio.h>
#include <GL/glu.h>

#include "OpenGL-basico/entities/player.h"
#include "OpenGL-basico/entities/block.h"
#include "OpenGL-basico/entities/brick_block.h"
#include "OpenGL-basico/entities/metal_block.h"
#include "OpenGL-basico/entities/bomb.h"
#include "OpenGL-basico/geometry/vector3.h"
#include "OpenGL-basico/geometry/grid.h"
#include "OpenGL-basico/interfaces/gamehud.h"
#include "OpenGL-basico/interfaces/number.h"
#include "OpenGL-basico/interfaces/settings_screen.h"
#include "OpenGL-basico/textures/texture.h"
#include "OpenGL-basico/textures/texture_loader.h"
#include "OpenGL-basico/utils/clock.h"
#include "OpenGL-basico/utils/renderer.h"
#include "OpenGL-basico/scene/scene.h"
#include "OpenGL-basico/utils/lights_handler.h"

int main(int argc, char* argv[])
{
    auto settings = settings::get_instance();
    //INICIALIZACION
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "No se pudo iniciar SDL: " << SDL_GetError() << '\n';
        exit(1);
    }

    SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       settings->window_width, settings->window_height,
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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

    auto settings_screen = new ::settings_screen(settings->window_width, settings->window_height);
    auto displacement = vector3(0, 0, 0);

    const auto grass_texture = texture_loader::load_texture("../assets/textures/grass_1.jpg");
    const auto floor = grid(10, 10, 1, vector3(0, 1, 0));
    const auto bricks_texture = texture_loader::load_texture("../assets/textures/bricks_1.jpg");
    std::vector<block*> bloques;

    bloques.push_back(new brick_block(vector3(0.5, -0.5, 0), 1));
    bloques.push_back(new brick_block(vector3(1.5, -0.5, 0), 1));
    bloques.push_back(new metal_block(vector3(2.5, -0.5, 0), 1));
    bloques.push_back(new metal_block(vector3(1.5, -0.5, 1), 1));
    
    auto bomberman = player();
    auto current_scene = scene(&bomberman, vector3(0, 0, -5));

    //VARIABLES QUE SE USAN PARA CONTROLAR LOS FRAMES
    Uint32 lastFrameTime = clock::get_instance()->get_total_time();
    int frames = 0;
    Uint32 time = 0;

    //VARIABLE PARA CONTROLAR LA VELOCIDAD DEL JUEGO(ANIMACIONES, ETC.) ES INDEPENDIENTE DEL FRAMERATE
    float game_velocity = 1;

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        if (clock::get_instance()->get_is_paused())
        {
            glMatrixMode(GL_PROJECTION);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(-settings->window_width / 2, settings->window_width / 2, -settings->window_height / 2,
                    settings->window_height / 2, -1.0, 1.0);
            renderer::draw(settings_screen);
            glPopMatrix();
        }
        else
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
        switch (settings::get_instance()->game_velocity)
        //CONSTANTE CON LA QUE MULTIPLICAR LAS ANIMACIONES Y MOVIMIENTOS
        {
        case game_velocity::slow:
            game_velocity = 0.3f;
            break;
        case game_velocity::normal:
            game_velocity = 1;
            break;
        case game_velocity::fast:
            game_velocity = 2;
            break;
        default: break;
        }
        if (settings::get_instance()->wireframe_enabled)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        if (settings::get_instance()->textures_enabled)
        {
            glEnable(GL_TEXTURE_2D);
        }
        else
        {
            glDisable(GL_TEXTURE_2D);
        }

        if (settings::get_instance()->facetado_enabled)
        {
            glShadeModel(GL_FLAT);
        }
        else
        {
            glShadeModel(GL_SMOOTH);
        }

        current_scene.move_player(displacement);

        displacement.reset();

        current_scene.render_scene();
        lights_handler::get_instance()->set_light(current_scene.get_camera_mode(),
                                                  settings::get_instance()->light_color,
                                                  current_scene.get_camera()->get_position());

        renderer::draw(floor, grass_texture);
        for (const auto& bloqueRef : bloques) {
            if(bloqueRef->is_active())
                renderer::draw(*bloqueRef->get_block(), bloqueRef->get_texture());
        }
        
        //CONTROL DE FRAMES
        frames++;
        Uint32 currentFrameTime = clock::get_instance()->get_total_time();
        Uint32 deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        time += deltaTime;
        if (time >= 1000)
        {
            std::cout << "FPS: " << frames << "\n";
            frames = 0;
            time = 0;
        }

        if (deltaTime < 1000 / 60) //limita a 60fps maximo
        {
            SDL_Delay(1000 / 60 - deltaTime);
        }

        float elapsed_time = static_cast<float>(clock::get_ticks());
        current_scene.update_bomb(elapsed_time, bloques);
        //MANEJO DE EVENTOS
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                {
                    const float x_offset = static_cast<float>(event.motion.xrel) * elapsed_time * game_velocity;
                    const float y_offset = -static_cast<float>(event.motion.yrel) * elapsed_time * game_velocity;
                    std::cout << "Mouse movement: " << x_offset << ", " << y_offset << "\n";
                    current_scene.rotate_camera(x_offset, y_offset);
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT && clock::get_instance()->get_is_paused())
                {
                    settings_screen->handle_click(event.button.x, event.button.y);
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
                    displacement.set_x(0.1f * elapsed_time * game_velocity);
                    break;
                case SDLK_d:
                    std::cout << "RIGHT\n";
                    displacement.set_x(-0.1f * elapsed_time * game_velocity);
                    break;
                case SDLK_w:
                    std::cout << "UP\n";
                    displacement.set_z(0.1f * elapsed_time * game_velocity);
                    break;
                case SDLK_s:
                    std::cout << "DOWN\n";
                    displacement.set_z(-0.1f * elapsed_time * game_velocity);
                    break;
                case SDLK_v:
                    current_scene.toggle_camera();
                    break;
                case SDLK_p:
                    std::cout << "PAUSE\n";
                    clock::toggle_pause();
                    break;
                case SDLK_b:
                    current_scene.drop_bomb();
                    std::cout << "Bomb placed!\n";
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
