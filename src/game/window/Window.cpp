#include "Window.h"

Window::Window()
    : m_window(nullptr, SDL_DestroyWindow),
      m_renderer(nullptr, SDL_DestroyRenderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    SDL_Window *window = SDL_CreateWindow(
        "AI Overlord",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
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

Window::~Window()
{
}

void Window::drawFillRectWithColour(SDL_Rect *rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(
        this->m_renderer.get(),
        r, g, b, a);

    SDL_RenderFillRect(this->m_renderer.get(), rect);
}

void Window::pushRenderToWindow()
{
    SDL_RenderPresent(this->m_renderer.get());
}

void Window::clear()
{
    SDL_RenderClear(this->m_renderer.get());
}