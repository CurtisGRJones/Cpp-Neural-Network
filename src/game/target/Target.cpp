#include "Target.h"

Target::Target(
    int32_t x,
    int32_t y,
    int32_t w,
    int32_t h,
    uint8_t r,
    uint8_t g,
    uint8_t b,
    uint8_t a)
    : m_r(r), m_b(b), m_g(g), m_a(a)
{
    this->m_rect.x = x;
    this->m_rect.y = y;
    this->m_rect.w = w;
    this->m_rect.h = h;
}

Target::~Target()
{
}

void Target::draw(Window * window) {
    window->drawFillRectWithColour(
        &this->m_rect,
        this->m_r,
        this->m_g,
        this->m_b,
        this->m_a
    );
}

void Target::move(int32_t x, int32_t y) {
    this->m_rect.x = x;
    this->m_rect.y = y;
}

SDL_Rect* Target::getRect() {
    return &this->m_rect;
}


