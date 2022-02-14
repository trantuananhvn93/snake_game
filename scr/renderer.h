#pragma once
#ifndef RENDERER_H
#define RENDERER_H
#include <vector>
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "snake.h"

class Renderer {
public:
    Renderer(int screen_width, int screen_height,
        int grid_width, int grid_height);
    ~Renderer();

    SDL_Renderer* renderer;
    SDL_Window* window;
    int running;

    void Render(Snake const snake, SDL_Point const& food);
    void UpdateWindowTitle(int score, int fps);

private:
    const int screen_width;
    const int screen_height;
    const int grid_width;
    const int grid_height;
};

#endif