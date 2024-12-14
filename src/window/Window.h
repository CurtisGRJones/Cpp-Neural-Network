#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <memory>
#include <functional>

enum class HAlignment : char
{
    LEFT = 0,
    CENTER = 1,
    RIGHT = 2
};

enum class VAlignment : char
{
    TOP = 0,
    CENTER = 1,
    BOTTOM = 2
};

class Window
{
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

public:
    Window();
    ~Window();

    // TODO make these return for error checking
    void useColorWrapper(uint32_t rgba, std::function<void()> lambda);
    void useColorWrapper(uint8_t r, uint8_t g, uint8_t b, uint8_t a, std::function<void()> lambda);

    void setDrawColour(uint32_t rgba);
    void setDrawColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    void fillBackground(uint32_t rgba);
    void fillBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void fillBackground();

    void drawFullRect(SDL_Rect *rect, uint32_t rgba);
    void drawFullRect(SDL_Rect *rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void drawFullRect(SDL_Rect *rect);

    void drawPoint(uint32_t x, uint32_t y, uint32_t rgba);
    void drawPoint(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void drawPoint(uint32_t x, uint32_t y);

    void displayText(
        std::string str,
        int32_t x,
        int32_t y,
        TTF_Font *font,
        HAlignment alignX = HAlignment::LEFT,
        VAlignment alignY = VAlignment::TOP);
    
    void pushRenderToWindow();
    void clear();

    void destroy();
private: 
    uint8_t getRFromI32(uint32_t rgba);
    uint8_t getGFromI32(uint32_t rgba);
    uint8_t getBFromI32(uint32_t rgba);
    uint8_t getAFromI32(uint32_t rgba);
};
