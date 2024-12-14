#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

class Graph
{
private:
    // TODO make this configurable
    u_int32_t m_positionX = 0;
    u_int32_t m_positionY = 150;

    u_int32_t m_width = 600;
    u_int32_t m_height = 300;

    std::vector<float> *m_points;

public:
    Graph()
    {
    }

    Graph(std::vector<float> *points)
        : m_points(points)
    {
    }

    void useScoreVector(std::vector<float> *points)
    {
        m_points = points;
    }

    void draw(SDL_Renderer *renderer)
    {
        if(this->m_points == nullptr) {
            return;
        }

        SDL_SetRenderDrawColor(
            renderer,
            255,
            0,
            0,
            255
        );

        int pointCount = this->m_points->size();

        int bottom = this->m_positionY + this->m_height;
        int left = this->m_positionX;

        float hSpacing = this->m_width / float(pointCount);

        float maxVal = *(std::max_element(this->m_points->begin(), this->m_points->end()));
        float vSpacing = 
            maxVal == 0 ?
                float(this->m_height) / 2 :
                vSpacing = float(this->m_height) / maxVal;

        for (int i = 0; i < pointCount; i++)
        {
            int x = int(left + i * hSpacing);
            int y = int(bottom - this->m_points->at(i) * vSpacing);
            SDL_RenderDrawPoint(
                renderer,
                x,
                y
            );
        }
    }
};