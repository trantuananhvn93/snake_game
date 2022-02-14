
#include "a_star.h"

map::map(std::vector<SDL_Point> snake_body) {
    w = h = 32;
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            m[i][j] = 0;
    for (auto const& it : snake_body) {
        m[it.x][it.y] = 1;
    }
}

aStar::aStar(std::vector<SDL_Point> snake_body, SDL_Point snake_head, SDL_Point food) :m(snake_body) {
    start.x = snake_head.x;
    start.y = snake_head.y;
    end.x = food.x;
    end.y = food.y;
    neighbours[0] = point(0, -1); neighbours[1] = point(-1, 0);
    neighbours[2] = point(0, 1); neighbours[3] = point(1, 0);
}

int aStar::calcDist(point& p) {
    // need a better heuristic
    int x = end.x - p.x, y = end.y - p.y;
    return(x * x + y * y);
}

bool  aStar::isValid(point& p) {
    return (p.x > -1 && p.y > -1 && p.x < m.w&& p.y < m.h);
}

bool  aStar::existPoint(point& p, int cost) {
    std::list<node>::iterator i;
    i = std::find(closed.begin(), closed.end(), p);
    if (i != closed.end()) {
        if ((*i).cost + (*i).dist < cost) return true;
        else { closed.erase(i); return false; }
    }
    i = std::find(open.begin(), open.end(), p);
    if (i != open.end()) {
        if ((*i).cost + (*i).dist < cost) return true;
        else { open.erase(i); return false; }
    }
    return false;
}

void  aStar::fillOpen(node& n) {
    int stepCost, nc, dist;
    point neighbour;

    for (int x = 0; x < 4; x++) {
        // one can make diagonals have different cost
        stepCost = 1;
        neighbour = n.pos + neighbours[x];

        if (isValid(neighbour) && m(neighbour.x, neighbour.y) != 1) {
            nc = stepCost + n.cost;
            dist = calcDist(neighbour);
            if (!existPoint(neighbour, nc + dist)) {
                node m;
                m.cost = nc; m.dist = dist;
                m.pos = neighbour;
                m.parent = n.pos;
                open.push_back(m);
            }
        }
    }
}



bool  aStar::search() {
    node n;
    n.cost = 0; n.pos = start; n.parent = 0; n.dist = calcDist(start);
    open.push_back(n);
    while (!open.empty()) {
        //std::sort(open.begin(), open.end());
        open.sort();
        node n = open.front();
        open.pop_front();
        closed.push_back(n);
        if (n == end){
            return true;
        }
        fillOpen(n);
    }
    return false;
}

int  aStar::path(std::list<point>& path) {
    int cost = closed.back().cost; 
    path.push_front(closed.back().pos);
    point parent = closed.back().parent;
    for (std::list<node>::reverse_iterator i = closed.rbegin(); i != closed.rend(); i++) {
        if ((*i).pos == parent && !((*i).pos == start)) {
            path.push_front((*i).pos);
            parent = (*i).parent;
        }
    }
    return cost;
}

void aStar::getClosedNodes(std::list<point>& nodes) {
    for (auto const& i : open) {
        nodes.push_back(i.pos);
    }
    for (auto const& i : closed) {
        nodes.push_back(i.pos);
    }
}