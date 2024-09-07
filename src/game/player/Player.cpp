#include "Player.h"

Player::Player(
    int32_t x,
    int32_t y,
    int32_t w,
    int32_t h,
    uint8_t r,
    uint8_t g,
    uint8_t b,
    uint8_t a)
    : m_r(r), m_g(g), m_b(b), m_a(a),
      m_mU(0), m_mR(0)
{
    this->m_rect.x = x;
    this->m_rect.y = y;
    this->m_rect.w = w;
    this->m_rect.h = h;
}

Player::~Player()
{
}

void Player::draw(Window *window)
{
    window->drawFillRectWithColour(
        &this->m_rect,
        this->m_r,
        this->m_g,
        this->m_b,
        this->m_a);
}

void Player::tick()
{
    this->m_rect.x += this->m_mR;
    this->m_rect.y += this->m_mU;

    if (this->m_rect.x > (600 - 30))
    {
        this->m_mR = -this->m_mR;
        this->m_rect.x = (600 - 30);
    }
    else if (this->m_rect.x < (0))
    {
        this->m_mR = -this->m_mR;
        this->m_rect.x = 0;
    }

    if (this->m_rect.y > (600 - 30))
    {
        this->m_mU = -this->m_mU;
        this->m_rect.y = (600 - 30);
    }
    else if (this->m_rect.y < (0))
    {
        this->m_mU = -this->m_mU;
        this->m_rect.y = 0;
    }
}

void Player::handleEvent(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        switch (event->key.keysym.scancode)
        {
        case SDL_SCANCODE_W:
            this->changeMomentumByDirection(0);
            break;
        case SDL_SCANCODE_S:
            this->changeMomentumByDirection(1);
            break;
        case SDL_SCANCODE_D:
            this->changeMomentumByDirection(2);
            break;
        case SDL_SCANCODE_A:
            this->changeMomentumByDirection(3);
            break;
        }
        break;
    }
}

void Player::changeMomentum(int32_t deltaMU, int32_t deltaMR)
{
    this->m_mU += deltaMU;
    this->m_mR += deltaMR;

    if (this->m_mU > 10)
    {
        this->m_mU = 10;
    }
    else if (this->m_mU < -10)
    {
        this->m_mU = -10;
    }

    if (this->m_mR > 10)
    {
        this->m_mR = 10;
    }
    else if (this->m_mR < -10)
    {
        this->m_mR = -10;
    }
}

void Player::addPoint()
{
    this->m_points++;
}

uint32_t Player::getPoints()
{
    return this->m_points;
}

void Player::resetPoints()
{
    this->m_points = 0;
}

SDL_Rect *Player::getRect()
{
    return &this->m_rect;
}

int32_t *Player::getMU()
{
    return &this->m_mU;
}

int32_t *Player::getMR()
{
    return &this->m_mR;
}

void Player::changeMomentumByDirection(int32_t direction)
{
    // TODO make this enum based
    switch (direction)
    {
    case 0:
        this->changeMomentum(-this->m_mDelta, 0);
        break;
    case 1:
        this->changeMomentum(this->m_mDelta, 0);
        break;
    case 2:
        this->changeMomentum(0, this->m_mDelta);
        break;
    case 3:
        this->changeMomentum(0, -this->m_mDelta);
        break;
    }
}

void Player::moveAndFreeze(uint32_t x, uint32_t y)
{
    this->m_mU = 0;
    this->m_mR = 0;
    this->m_rect.x = x;
    this->m_rect.y = y;
}
