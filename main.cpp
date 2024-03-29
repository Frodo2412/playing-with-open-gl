#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>

#include "OpenGL-basico/models/Triangle.h"
#include "OpenGL-basico/models//vector.h"

using namespace std;

void draw_vertex(vector vertex)
{
    glVertex3f(vertex.get_x(), vertex.get_y(), vertex.get_z());
}

void draw_triangle(triangle triangle)
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    draw_vertex(triangle.get_a());
    glColor3f(1.0, 0.0, 0.0);
    draw_vertex(triangle.get_b());
    glColor3f(0.0, 0.0, 1.0);
    draw_vertex(triangle.get_c());
    glEnd();
}

int main(int argc, char* argv[])
{
    //INICIALIZACION
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
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

    const auto camera = vector(0, 0, 5);
    const auto main_triangle = triangle(vector(1, -1, 0), vector(-1, -1, 0), vector(0, 1, 0));

    float degrees = 0;

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(camera.get_x(), camera.get_y(), camera.get_z(), 0, 0, 0, 0, 1, 0);

        if (rotate)
        {
            degrees = degrees + 0.1f;
        }
        glRotatef(degrees, 0.0, 1.0, 0.0);

        draw_triangle(main_triangle);

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
            case SDL_QUIT:
                fin = true;
                break;
            case SDL_KEYUP:
                switch (evento.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    fin = true;
                    break;
                case SDLK_RIGHT:
                    break;
                }
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
