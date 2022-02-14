#include "game.h"

void Game::Run(Renderer& renderer, int target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        FindPath();
        Update();
        renderer.Render(snake, food);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
        //running = false;
    }
}

void Game::FindPath() {
    snake.path.clear();
    snake.found_nodes.clear();
    aStar as(snake.body, snake.head, food);
    
    if (as.search()) {
        std::list<point> path;
        int c = as.path(path);
        //std::cout << "\nPath cost " << c << ": ";
        for (std::list<point>::iterator i = path.begin(); i != path.end(); i++) {            
            //std::cout << "(" << (*i).x << ", " << (*i).y << ") ";
            SDL_Point p{ (*i).x , (*i).y };
            snake.path.push_back(p);
        }
        std::list<point> nodes;
        as.getClosedNodes(nodes);
        //std::cout << "closed nodes:" << nodes.size() << "\n";
        for (auto const& i : nodes) {
            snake.found_nodes.push_back(SDL_Point {i.x, i.y});
        }
    }

}

void Game::PlaceFood() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing
        // food.
        if (!snake.SnakeCell(x, y)) {
            food.x = x;
            food.y = y;
            return;
        }
    }
}

void Game::Update() {
    if (!snake.alive) return;

    snake.Update();

    int new_x = snake.head.x;
    int new_y = snake.head.y;

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
        score++;
        PlaceFood();
        // Grow snake and increase speed.
        snake.GrowBody();       
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }