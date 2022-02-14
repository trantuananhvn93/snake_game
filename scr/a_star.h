#pragma once
#ifndef ASTAR_H
#define ASTAR_H
#include <list>
#include <algorithm>
#include <iostream>
#include "SDL.h"
#include <vector>

class point {
public:
    point(int a = 0, int b = 0) { x = a; y = b; }
    bool operator ==(const point& o) { return o.x == x && o.y == y; }
    point operator +(const point& o) { return point(o.x + x, o.y + y); }
    int x, y;
};

class map {
public:
    map(std::vector<SDL_Point> snake_body);
    int operator() (int x, int y) { return m[x][y]; }
    char m[32][32];
    int w, h;


};

class node {
public:
    bool operator == (const node& o) { return pos == o.pos; }
    bool operator == (const point& o) { return pos == o; }
    bool operator < (const node& o) { return dist + cost < o.dist + o.cost; }

    point pos, parent;
    int dist, cost;
};



class aStar {
public:
    aStar(std::vector<SDL_Point> snake_body, SDL_Point snake_head, SDL_Point food);

    int calcDist(point& p);
    bool isValid(point& p);
    bool existPoint(point& p, int cost);
    void fillOpen(node& n);
    bool search();
    int path(std::list<point>& path);
    void getClosedNodes(std::list<point>& nodes);
    map m; 
    point end, start;
    point neighbours[4];
    std::list<node> open;
    std::list<node> closed;
};


#endif

