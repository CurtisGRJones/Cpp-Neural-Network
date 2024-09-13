#include "NNDisplay.h"

NNDisplay::NNDisplay(Ai *ai)
    : m_ai(ai),
      m_window(nullptr, SDL_DestroyWindow),
      m_renderer(nullptr, SDL_DestroyRenderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    SDL_Window *window = SDL_CreateWindow(
        "AI Overlord NN",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        300,
        0);

    if (!window)
    {
        SDL_Quit();
        throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
    }

    m_window.reset(window);

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        0);

    if (!renderer)
    {
        throw std::runtime_error("Failed to create SDL_Renderer: " + std::string(SDL_GetError()));
    }

    m_renderer.reset(renderer);
}

NNDisplay::~NNDisplay()
{
}

void NNDisplay::changeAi(Ai *ai)
{
    this->m_ai = ai;
}

void NNDisplay::draw()
{
    
}
