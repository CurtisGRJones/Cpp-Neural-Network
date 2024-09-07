#pragma once

#include <SDL2/SDL.h>
#include "../window/Window.h"

class Player
{
private:
    SDL_Rect m_rect;
    uint8_t m_r, m_g, m_b, m_a;
    int32_t m_mU, m_mR;
    const uint32_t m_mDelta = 1;
    void changeMomentum(int32_t deltaMU, int32_t deltaMR);
    uint64_t m_points = 0;

public:
    Player(
        int32_t x,
        int32_t y,
        int32_t w,
        int32_t l,
        uint8_t r,
        uint8_t g,
        uint8_t b,
        uint8_t a);
    ~Player();

    void draw(Window *window);
    void tick();
    void handleEvent(SDL_Event *event);
    void addPoint();
    uint32_t getPoints();
    void resetPoints();
    SDL_Rect *getRect();

    int32_t *getMU();
    int32_t *getMR();

    void changeMomentumByDirection(int32_t direction);
    void moveAndFreeze(uint32_t x, uint32_t y);
};
