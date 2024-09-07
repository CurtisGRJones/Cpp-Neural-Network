#pragma once

#include <SDL2/SDL.h>
#include "../window/Window.h"

class Target
{
private:
    SDL_Rect m_rect;
    uint8_t m_r, m_g, m_b, m_a;

public:
    Target(
        int32_t x,
        int32_t y,
        int32_t w,
        int32_t l,
        uint8_t r,
        uint8_t g,
        uint8_t b,
        uint8_t a);
    ~Target();

    void draw(Window *window);
    void move(int32_t x, int32_t y);
    SDL_Rect* getRect();
};