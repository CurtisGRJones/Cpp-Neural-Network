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

    void fillBackground(uint32_t rgba);
    void fillBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void drawFillRectWithColour(SDL_Rect *rect, uint32_t rgba);
    void drawFillRectWithColour(SDL_Rect *rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void pushRenderToWindow();
    void clear();
private: 
    uint8_t getRFromI32(uint32_t rgba);
    uint8_t getGFromI32(uint32_t rgba);
    uint8_t getBFromI32(uint32_t rgba);
    uint8_t getAFromI32(uint32_t rgba);
};
