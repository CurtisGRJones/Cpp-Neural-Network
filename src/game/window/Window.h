#pragma once

#include <SDL2/SDL.h>
#include <memory>

class Window
{
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

public:
    Window();
    ~Window();

    void drawFillRectWithColour(SDL_Rect *rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void pushRenderToWindow();
    void clear();
};
