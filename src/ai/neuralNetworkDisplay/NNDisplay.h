#pragma once

#include <SDL2/SDL.h>
#include "../Ai.h"

class NNDisplay
{
private:
    Ai *m_ai;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

public:
    NNDisplay(Ai *ai);
    ~NNDisplay();

    void changeAi(Ai *ai);

    void draw();
};