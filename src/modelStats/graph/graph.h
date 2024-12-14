#pragma once

#include <SDL2/SDL.h>
#include <vector>


class Graph
{
private:
    // TODO make this configurable in constructor
    u_int32_t m_positionX = 0;
    u_int32_t m_positionY = 150;

    u_int32_t m_width = 600;
    u_int32_t m_height = 300;

    std::vector<float> *m_points;

public:
    Graph();
    Graph(std::vector<float> *points);

    void useScoreVector(std::vector<float> *points);

    void draw(SDL_Renderer *renderer);
};