#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
    SDL_Point prev_cell = head;  // We first capture the head's cell before updating.
    UpdateHead();
    SDL_Point current_cell = head;  // Capture the head's cell after updating.

    // Update all of the body vector items if the snake head has moved to a new
    // cell.
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
        UpdateBody(current_cell, prev_cell);
    }
}

void Snake::UpdateHead() {
    if (path.size()) {
        //std::cout << "size:" << path.size() <<"\n";
        head = path.front();
    }

    // Wrap the Snake around to the beginning if going off of the screen.
    head.x = fmod(head.x + grid_width, grid_width);
    head.y = fmod(head.y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point& current_head_cell, SDL_Point& prev_head_cell) {
    // Add previous head location to vector
    body.push_back(prev_head_cell);

    if (!growing) {
        // Remove the tail from the vector.
        body.erase(body.begin());
    }
    else {
        growing = false;
        size++;
    }

    // Check if the snake has died.
    for (auto const& item : body) {
        if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
            alive = false;
        }
    }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
    if (x == static_cast<int>(head.x) && y == static_cast<int>(head.y)) {
        return true;
    }
    for (auto const& item : body) {
        if (x == item.x && y == item.y) {
            return true;
        }
    }
    return false;
}