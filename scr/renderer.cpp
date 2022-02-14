#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(int screen_width, int screen_height,
    int grid_width, int grid_height) : screen_width(screen_width),
    screen_height(screen_height),
    grid_width(grid_width),
    grid_height(grid_height)
{
    running = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

}

Renderer::~Renderer() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const& food) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0x10, 0x15, 0x1E, 0xFF);
    SDL_RenderClear(renderer);

    // Render food
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(renderer, &block);

    // Render snake's body
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const& point : snake.body) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer, &block);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &block);
    }

    // Render snake's head
    block.x = snake.head.x * block.w;
    block.y = snake.head.y * block.h;
    if (snake.alive) {
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(renderer, &block);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(renderer, &block);

    // Render found nodes
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    for (SDL_Point const& point : snake.found_nodes) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderDrawRect(renderer, &block);
    }

    // Render snake's path
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const& point : snake.path) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderDrawRect(renderer, &block);
    }    

    // Update Screen
    SDL_RenderPresent(renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
    std::string title{ "Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) };
    SDL_SetWindowTitle(window, title.c_str());
}