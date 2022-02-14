#pragma once
#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
public:
    Snake(int grid_width, int grid_height)
        : 
        grid_width(grid_width),
        grid_height(grid_height)
    {
        head.x = static_cast<int>(grid_width / 2);
        head.y = static_cast<int>(grid_height / 2);
    }

    enum class Direction { kUp, kDown, kLeft, kRight, kNone };
    void Update();

    void GrowBody();
    bool SnakeCell(int x, int y);

    Direction direction = Direction::kUp;

    int speed{ 1 };
    int size{ 1 };
    bool alive{ true };
    std::vector<SDL_Point> body;
    std::vector<SDL_Point> path;
    std::vector<SDL_Point> found_nodes;
    SDL_Point head;

    

private:
    void UpdateHead();
    void UpdateBody(SDL_Point& current_cell, SDL_Point& prev_cell);

    bool growing{ false };

    const int grid_width;
    const int grid_height;
};

#endif