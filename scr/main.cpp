#include <iostream>
#include "renderer.h"
#include "game.h"

// You shouldn't really use this statement, but it's fine for small programs
using namespace std;

int main(int argc, char** args) {
    const int fps = 20;
    const int ms_per_frame = 1000 / fps;
    const int screen_width = 640;
    const int screen_height = 640;
    const int grid_width = 32;
    const int grid_height = 32;

    std::cout << "Welcome to the Game\n";
   
    Renderer renderer(screen_width, screen_height, grid_width, grid_height);
    //Controller controller;
    Game game(grid_width, grid_height);
    game.Run(renderer, ms_per_frame);
    /*Snake snake(grid_width, grid_height);
    SDL_Point food{ 10,10 };
    renderer.Render(snake, food);*/
    /*while (1) {

    }*/
    /*game.Run(controller, renderer, kMsPerFrame);
    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";*/

	return 0;
};


