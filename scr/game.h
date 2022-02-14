#ifndef GAME_H
#define GAME_H


#include <iostream>
#include <random>
#include <memory>
#include "SDL.h"
#include "renderer.h"
#include "snake.h"
#include "a_star.h"


class Game {
 public:
	 Game(int grid_width, int grid_height):snake(grid_width, grid_height),
		 engine(dev()),
		 random_w(0, static_cast<int>(grid_width) - 1),
		 random_h(0, static_cast<int>(grid_height) - 1) {
	 };
	 ~Game() {};
	 void Run(Renderer& renderer, int target_frame_duration);

	 //void Run(Controller const& controller, Renderer& renderer, std::size_t target_frame_duration);
	 int GetScore() const;
	 int GetSize() const;
 private:
	 Snake snake;
	 SDL_Point food;


	 std::random_device dev;
	 std::mt19937 engine;
	 std::uniform_int_distribution<int> random_w;
	 std::uniform_int_distribution<int> random_h;

	 int score{ 0 };

	 void PlaceFood();
	 void Update();
	 void SetPlayer();
	 void FindPath();
};

#endif