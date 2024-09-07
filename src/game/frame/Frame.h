#pragma once

#include "../window/Window.h"
#include "../player/Player.h"
#include "../target/Target.h"

#include <random>

class Frame
{
private:
    Player m_player;
    Target m_target;

    SDL_Rect backGround;

    int32_t getRandomTargetCord();

public:
    Frame();
    ~Frame();

    void tick();
    void draw(Window *window);
    void handleEvent(SDL_Event *event);

    Player *getPlayer();
    Target *getTarget();

    void reset();
};

Frame::Frame()
    : m_player(
          Player(
              (600 / 2) - 15,
              (600 / 2) - 15,
              30,
              30,
              255,
              0,
              0,
              255)),
      m_target(
          Target(
              this->getRandomTargetCord(),
              this->getRandomTargetCord(),
              30,
              30,
              0,
              255,
              0,
              255))
{
    this->backGround.x = 0;
    this->backGround.y = 0;
    this->backGround.w = 600;
    this->backGround.h = 600;
}

Frame::~Frame()
{
}

int32_t Frame::getRandomTargetCord()
{
    return std::rand() % (600 - 30);
}

void Frame::tick()
{
    if ( SDL_HasIntersection(this->m_target.getRect(), this->m_player.getRect()) )
    {
        this->m_player.addPoint();
        this->m_target.move(
            this->getRandomTargetCord(),
            this->getRandomTargetCord());
    }
    this->m_player.tick();
}

void Frame::draw(Window *window)
{
    window->drawFillRectWithColour(
        &this->backGround,
        100,
        100,
        100,
        255);
    this->m_target.draw(window);
    this->m_player.draw(window);
}

void Frame::handleEvent(SDL_Event *event)
{
    this->m_player.handleEvent(event);
}

Player *Frame::getPlayer()
{
    return &this->m_player;
}

Target *Frame::getTarget()
{
    return &this->m_target;
}

void Frame::reset()
{
    this->m_player.moveAndFreeze(
        (600 / 2) - 15,
        (600 / 2) - 15);
    this->m_player.resetPoints();
    this->m_target.move(
        this->getRandomTargetCord(),
        this->getRandomTargetCord());
}
