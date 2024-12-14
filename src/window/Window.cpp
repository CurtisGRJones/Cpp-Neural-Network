#include "Window.h"

#include <iostream>

Window::Window()
    : m_window(nullptr, SDL_DestroyWindow),
      m_renderer(nullptr, SDL_DestroyRenderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return;
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

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    m_renderer.reset(renderer);
}

Window::~Window()
{
}

void Window::useColorWrapper(uint32_t rgba, std::function<void()> lambda)
{
    return this->useColorWrapper(
        this->getRFromI32(rgba),
        this->getGFromI32(rgba),
        this->getBFromI32(rgba),
        this->getAFromI32(rgba),
        lambda);
}

void Window::useColorWrapper(uint8_t r, uint8_t g, uint8_t b, uint8_t a, std::function<void()> lambda)
{
    Uint8 originalR, originalG, originalB, originalA;
    SDL_GetRenderDrawColor(this->m_renderer.get(), &originalR, &originalG, &originalB, &originalA);
    SDL_SetRenderDrawColor(this->m_renderer.get(), r, g, b, a);
    lambda();
    SDL_SetRenderDrawColor(this->m_renderer.get(), originalR, originalG, originalB, originalA);
}

void Window::setDrawColour(uint32_t rgba)
{
    return this->setDrawColour(
        this->getRFromI32(rgba),
        this->getGFromI32(rgba),
        this->getBFromI32(rgba),
        this->getAFromI32(rgba));
}

void Window::setDrawColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(
        this->m_renderer.get(),
        r, g, b, a);
}

void Window::fillBackground(uint32_t rgba)
{
    this->useColorWrapper(
        rgba, [this]()
        { return this->fillBackground(); });
}

void Window::fillBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    this->useColorWrapper(
        r, g, b, a, [this]()
        { return this->fillBackground(); });
}

void Window::fillBackground()
{
    int32_t width, height;

    SDL_GetWindowSize(this->m_window.get(), &width, &height);

    SDL_Rect rect = SDL_Rect{
        0,
        0,
        width,
        height};

    this->drawFullRect(&rect);
}

void Window::drawFullRect(SDL_Rect *rect, uint32_t rgba)
{
    this->useColorWrapper(
        rgba,
        [this, rect]()
        { return this->drawFullRect(rect); });
}

void Window::drawFullRect(SDL_Rect *rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    this->useColorWrapper(
        r, g, b, a, [this, rect]()
        { return this->drawFullRect(rect); });
}

void Window::drawFullRect(SDL_Rect *rect)
{
    SDL_RenderFillRect(this->m_renderer.get(), rect);
}

void Window::drawPoint(uint32_t x, uint32_t y, uint32_t rgba)
{
    return this->useColorWrapper(rgba, [this, x, y]()
                                 { return this->drawPoint(x, y); });
}
void Window::drawPoint(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return this->useColorWrapper(r, g, b, a, [this, x, y]()
                                 { return this->drawPoint(x, y); });
}
void Window::drawPoint(uint32_t x, uint32_t y)
{
    SDL_RenderDrawPoint(this->m_renderer.get(), x, y);
}

void Window::displayText(
    std::string str,
    int32_t x,
    int32_t y,
    TTF_Font *font,
    HAlignment alignX,
    VAlignment alignY)
{
    if (font == nullptr)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(this->m_renderer.get());
        SDL_DestroyWindow(this->m_window.get());
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(
        font,
        str.c_str(),
        {255, 255, 255, 255});

    if (textSurface == nullptr)
    {
        std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        SDL_DestroyRenderer(this->m_renderer.get());
        SDL_DestroyWindow(this->m_window.get());
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(
        this->m_renderer.get(),
        textSurface);

    if (textTexture == nullptr)
    {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(this->m_renderer.get());
        SDL_DestroyWindow(this->m_window.get());
        TTF_Quit();
        SDL_Quit();
        return;
    }

    int32_t quadX = x;

    if (alignX == HAlignment::CENTER)
    {
        quadX -= textSurface->w / 2;
    }
    else if (alignX == HAlignment::RIGHT)
    {
        quadX -= textSurface->w;
    }

    int32_t quadY = y;

    if (alignY == VAlignment::CENTER)
    {
        quadX -= textSurface->h / 2;
    }
    else if (alignY == VAlignment::BOTTOM)
    {
        quadX -= textSurface->h;
    }

    SDL_Rect renderQuad = {
        quadX,
        quadY,
        textSurface->w,
        textSurface->h};

    SDL_RenderCopy(this->m_renderer.get(), textTexture, NULL, &renderQuad);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Window::pushRenderToWindow()
{
    SDL_RenderPresent(this->m_renderer.get());
}

void Window::clear()
{
    SDL_RenderClear(this->m_renderer.get());
}

void Window::destroy()
{
    SDL_DestroyRenderer(this->m_renderer.get());
    SDL_DestroyWindow(this->m_window.get());
}

uint8_t Window::getRFromI32(uint32_t rgba)
{
    return (rgba >> 24) & 0xFF;
}
uint8_t Window::getGFromI32(uint32_t rgba)
{
    return (rgba >> 16) & 0xFF;
}
uint8_t Window::getBFromI32(uint32_t rgba)
{
    return (rgba >> 8) & 0xFF;
}
uint8_t Window::getAFromI32(uint32_t rgba)
{
    return rgba & 0xFF;
}