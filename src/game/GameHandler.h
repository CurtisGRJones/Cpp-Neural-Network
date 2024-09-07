#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <chrono>
#include "window/Window.h"
#include "frame/Frame.h"

class GameHandler
{
private:
    bool m_running = true;
    bool m_useUserInputs;
    bool m_consitantFrameRate = true;
    Window m_window;
    std::shared_ptr<Frame> m_frame;
    SDL_Event m_event;
    std::chrono::time_point<std::chrono::system_clock> m_previousFrameTime = std::chrono::system_clock::now();

public:
    GameHandler(bool useUserInputs = true);
    GameHandler(bool useUserInputs, std::shared_ptr<Frame> frame, bool consitantFrameRate = true);
    ~GameHandler();

    bool isRunning();
    void draw();
    void tick();
    int quitGame();

    void handleEvents();

    std::shared_ptr<Frame> getFrame();
    void changeFrame(std::shared_ptr<Frame> frame);
};
