#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <conio.h>
#include <GL/glu.h>

#include "OpenGL-basico/geometry/vector3.h"
#include "OpenGL-basico/interfaces/gamehud.h"
#include "OpenGL-basico/interfaces/number.h"
#include "OpenGL-basico/interfaces/settings_screen.h"
#include "OpenGL-basico/utils/clock.h"
#include "OpenGL-basico/utils/renderer.h"
#include "OpenGL-basico/utils/sound.h"
#include "OpenGL-basico/scene/scene.h"
#include "OpenGL-basico/utils/game_over_exception.h"
#include "OpenGL-basico/utils/lights_handler.h"
#include "OpenGL-basico/utils/next_level_exception.h"
#include "OpenGL-basico/utils/particles_handler.h"
#include "OpenGL-basico/interfaces/menu.h"

void handle_events(settings_screen* settings_screen, scene& current_scene, vector3& displacement, bool& fin,
                   float delta_time, sound& bomb_planted);
void update_game_state(scene& current_scene, vector3& displacement, float delta_time, sound& explosion);
void render_everything(settings_screen* settings_screen, const scene& current_scene, float seconds, float game_velocity);

int main(int argc, char* argv[])
{
    auto settings = settings::get_instance();
    //INICIALIZACION
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "No se pudo iniciar SDL: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       settings->window_width, settings->window_height,
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(win);

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "No se pudo iniciar SDL para audio: " << SDL_GetError() << '\n';
        return 1;
    }

    //sound sound1("../assets/music/Bomberman Theme (Area 1).wav");
    sound bomb_planted("../assets/music/Bomb_Planted.wav");
    sound explosion("../assets/music/Explosion.wav");

    if (!bomb_planted.load() || !explosion.load())
    {
        SDL_Log("Error al cargar sonidos.");
        SDL_Quit();
        return 1;
    }


    SDL_SetWindowGrab(win, SDL_TRUE);

    glMatrixMode(GL_PROJECTION);

    constexpr float color = 0;
    glClearColor(color, color, color, 1);

    gluPerspective(45, 640 / 480.f, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

    bool fin = false;
    texture_manager::init();
    clock::init();
    number::init();
    gamehud::init();

    const auto settings_screen = new ::settings_screen(settings->window_width, settings->window_height);
    auto displacement = vector3(0, 0, 0);

    scene* current_scene = scene::get_level(1, first);

    //VARIABLES QUE SE USAN PARA CONTROLAR LOS FRAMES
    Uint32 last_frame_time = clock::get_total_time();
    int frames = 0;
    Uint32 time = 0;

    //VARIABLE PARA CONTROLAR LA VELOCIDAD DEL JUEGO(ANIMACIONES, ETC.) ES INDEPENDIENTE DEL FRAMERATE
    float game_velocity = 1;
    

    do
    {
        switch (settings::get_instance()->game_velocity)
        //CONSTANTE CON LA QUE MULTIPLICAR LAS ANIMACIONES Y MOVIMIENTOS
        {
        case slow:
            game_velocity = 0.3;
            break;
        case normal:
            game_velocity = 1;
            break;
        case fast:
            game_velocity = 2;
            break;
        default: break;
        }

        //CONTROL DE FRAMES
        frames++;
        const Uint32 current_frame_time = clock::get_total_time();
        const Uint32 delta_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;
        time += delta_time;
        if (time >= 1000)
        {
            std::cout << "FPS: " << frames << "\n";
            frames = 0;
            time = 0;
        }

        if (delta_time < 1000 / 60) //limita a 60fps maximo
        {
            SDL_Delay(1000 / 60 - delta_time);
        }

        const float elapsed_time = static_cast<float>(clock::get_ticks());

        try
        {
            handle_events(settings_screen, *current_scene, displacement, fin, elapsed_time * game_velocity,
                          bomb_planted);
            update_game_state(*current_scene, displacement, elapsed_time * game_velocity, explosion);

            render_everything(settings_screen, *current_scene, clock::get_total_time() / 1000, game_velocity);
            //DIVIDIDO 100 PORQUE ES EN SEGUNDOS
            SDL_GL_SwapWindow(win);
        }
        catch (game_over_exception& e)
        {
            menu::get_instance()->set_started(false);
            menu::get_instance()->set_victory(false);
            current_scene = scene::get_level(current_scene->level_number, first);
            gamehud::reset_score();
            displacement.reset();
            clock::reset();
        }
        catch (next_level_exception& e)
        {
            if (current_scene->level_number < 5)
            {
                current_scene = scene::get_level(current_scene->level_number + 1, current_scene->get_camera_mode() );
                displacement.reset();
                clock::reset();
            }
            else
            {
                menu::get_instance()->set_started(false);
                menu::get_instance()->set_victory(true);
                current_scene = scene::level1();
                gamehud::reset_score();
                displacement.reset();
                clock::reset();
                std::cout << "GANASTE" << current_scene->level_number << std::endl;
            }
        }
    }
    while (!fin);
    //FIN LOOP PRINCIPAL
    // LIMPIEZA
    SDL_SetWindowGrab(win, SDL_FALSE);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}


void handle_events(settings_screen* settings_screen, scene& current_scene, vector3& displacement, bool& fin,
                   const float delta_time, sound& bomb_planted)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION:
            {
                const float x_offset = static_cast<float>(event.motion.xrel) * delta_time;
                const float y_offset = -static_cast<float>(event.motion.yrel) * delta_time;
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
            if (event.button.button == SDL_BUTTON_LEFT && !clock::get_instance()->get_is_paused())
            {
                if (!menu::get_instance()->get_started())
                {
                    menu::get_instance()->handle_event(event.button.x, event.button.y);
                }
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
                displacement.set_x(0.01f * delta_time);
                break;
            case SDLK_d:
                std::cout << "RIGHT\n";
                displacement.set_x(-0.01f * delta_time);
                break;
            case SDLK_w:
                std::cout << "UP\n";
                displacement.set_z(0.01f * delta_time);
                break;
            case SDLK_s:
                std::cout << "DOWN\n";
                displacement.set_z(-0.01f * delta_time);
                break;
            case SDLK_v:
                current_scene.toggle_camera();
                break;
            case SDLK_p:
                std::cout << "PAUSE\n";
                clock::toggle_pause();
                break;
            case SDLK_b:
                bomb_planted.play();
                current_scene.drop_bomb();
                std::cout << "Bomb placed!\n";
                break;
            default: break;
            }
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                fin = true;
                break;
            case SDLK_q:
                fin = true;
                break;
            default: break;
            }
        default: break;
        }
    }
}

void update_game_state(scene& current_scene, vector3& displacement, const float delta_time, sound& explosion)
{
    current_scene.move_player(displacement);
    displacement.reset();
    current_scene.update_scene(delta_time, explosion);
}

void render_everything(settings_screen* settings_screen, const scene& current_scene, float seconds, float game_velocity)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if (!menu::get_instance()->get_started())
    {
        if (clock::get_instance()->get_is_paused())
            renderer::draw(settings_screen);
        else
            renderer::draw(menu::get_instance());
        clock::get_instance()->reset();
    } else
    {
        if (clock::get_instance()->get_is_paused()) renderer::draw(settings_screen);
        else
        {
            renderer::draw(seconds, current_scene, game_velocity);
            renderer::draw_gamehud();
        }

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
        {
            std::cerr << "OpenGL error: " << err << std::endl;
        }
    }
}
