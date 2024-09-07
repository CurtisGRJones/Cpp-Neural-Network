#include "GameHandler.h"

GameHandler::GameHandler(bool useUserInputs)
    : m_useUserInputs(useUserInputs),
      m_frame(std::make_shared<Frame>(Frame()))
{
}

GameHandler::GameHandler(bool useUserInputs, std::shared_ptr<Frame> frame, bool consitantFrameRate)
    : m_useUserInputs(useUserInputs),
      m_frame(frame),
      m_consitantFrameRate(consitantFrameRate)
{
}

GameHandler::~GameHandler()
{
}

bool GameHandler::isRunning()
{
    return this->m_running;
}

void GameHandler::draw() {
    this->m_window.clear();
    this->m_frame->draw(&this->m_window);
    this->m_window.pushRenderToWindow();
}

void GameHandler::tick()
{

    this->handleEvents();

    this->m_frame->tick();

    this->draw();

    if (this->m_consitantFrameRate)
    {
        int32_t delay = int(1000 / 60) - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->m_previousFrameTime).count();

        if (delay > 0)
        {
            SDL_Delay(delay);
        }

        this->m_previousFrameTime = std::chrono::system_clock::now();
    }
}

int GameHandler::quitGame()
{
    this->m_running = 0;
    SDL_Quit();
    return 0;
}

void GameHandler::handleEvents()
{
    while (SDL_PollEvent(&this->m_event))
    {
        switch (this->m_event.type)
        {
        case SDL_QUIT:
            this->quitGame();
            break;
        default:
            if (this->m_useUserInputs)
            {
                this->m_frame->handleEvent(&this->m_event);
            }
        }

        if (!this->m_running)
        {
            break;
        }
    }
}

std::shared_ptr<Frame> GameHandler::getFrame()
{
    return this->m_frame;
}

void GameHandler::changeFrame(std::shared_ptr<Frame> frame)
{
    this->m_frame = frame;
}
