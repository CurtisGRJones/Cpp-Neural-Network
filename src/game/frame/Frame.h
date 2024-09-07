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
