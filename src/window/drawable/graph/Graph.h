#pragma once

#include "../../Window.h"


class Graph
{
public:
    static void drawFromVector(
        Window *window, 
        std::vector<float> *values, 
        SDL_Rect rect, 
        uint32_t fgColor=0xFFFFFFFF, 
        uint32_t bgColour=0x00000000);
};