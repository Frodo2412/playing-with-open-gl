#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <conio.h>
#include <GL/glu.h>

#include "OpenGL-basico/geometry/Triangle.h"
#include "OpenGL-basico/geometry//vector.h"

using namespace std;

const vector rotation_axis = vector(0, 1, 0);

enum zoom
{
    in,
    out
};

void draw_vertex(const vector& vertex)
{
    glVertex3f(vertex.get_x(), vertex.get_y(), vertex.get_z());
}

void draw_triangle(const triangle& triangle)
{
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    draw_vertex(triangle.get_a());
    glColor3f(1.0, 0.0, 0.0);
    draw_vertex(triangle.get_b());
    glColor3f(0.0, 0.0, 1.0);
    draw_vertex(triangle.get_c());
    glEnd();
}

void zoom(vector& camera, const zoom zoom)
{
    switch (zoom)
    {
    case in:
        cout << "Zooming in!\n";
        camera.set_z(camera.get_z() - 0.1f);
        break;
    case out:
        cout << "Zooming out!\n";
        camera.set_z(camera.get_z() + 0.1f);
    }
}

void draw_pyramid()
{
    const auto base = triangle(vector(1, 0, 0), vector(-1, 0, -1), vector(-1, 0, 1));
    auto apex = vector(0, 2, 0);
    auto front = triangle(base.get_a(), base.get_b(), apex);
    auto right = triangle(base.get_b(), base.get_c(), apex);
    auto back = triangle(base.get_c(), base.get_a(), apex);

    draw_triangle(base);
    draw_triangle(front);
    draw_triangle(right);
    draw_triangle(back);
}

int main(int argc, char* argv[])
{
    //INICIALIZACION
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << '\n';
        exit(1);
    }

    SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(win);

    glMatrixMode(GL_PROJECTION);

    float color = 0;
    glClearColor(color, color, color, 1);

    gluPerspective(45, 640 / 480.f, 0.1, 100);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

    bool fin = false;
    bool rotate = false;

    SDL_Event evento;

    auto camera = vector(0, 0, 5);
    auto main_triangle = triangle(vector(1, -1, 0), vector(-1, -1, 0), vector(0, 1, 0));

    float degrees = 0;
    auto displacement = vector(0, 0, 0);

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
        draw_pyramid();
        // draw_triangle(main_triangle);
        displacement.set_x(0);
        displacement.set_y(0);

        //MANEJO DE EVENTOS
        while (SDL_PollEvent(&evento))
        {
            switch (evento.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                rotate = true;
                cout << "ROT\n";
                break;
            case SDL_MOUSEBUTTONUP:
                rotate = false;
                break;
            case SDL_MOUSEWHEEL:
                if (evento.wheel.y > 0)
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
                switch (evento.key.keysym.sym)
                {
                case SDLK_a:
                    cout << "LEFT\n";
                    displacement.set_x(-0.1f);
                    break;
                case SDLK_d:
                    cout << "RIGHT\n";
                    displacement.set_x(0.1f);
                    break;
                case SDLK_w:
                    cout << "UP\n";
                    displacement.set_y(0.1f);
                    break;
                case SDLK_s:
                    cout << "DOWN\n";
                    displacement.set_y(-0.1f);
                    break;
                default: break;
                }
            case SDL_KEYUP:
                switch (evento.key.keysym.sym)
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
