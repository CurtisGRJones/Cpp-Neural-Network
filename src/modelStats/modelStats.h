#pragma once

#include <SDL2/SDL.h>
// #include <SDL_ttf/SDL_ttf.h>
#include <memory>
#include <vector>

#include "graph/graph.h"

class ModelStats
{
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    Graph m_graph;

    uint32_t *m_evolution;

public:
    ModelStats(uint32_t *evolution)
        : m_window(nullptr, SDL_DestroyWindow),
          m_renderer(nullptr, SDL_DestroyRenderer),
          m_evolution(evolution)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
        }

        SDL_Window *window = SDL_CreateWindow(
            "AI Overlord Training Stats",
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

    ~ModelStats()
    {
    }

    void useScoreVector(std::vector<float> *scores)
    {
        this->m_graph.useScoreVector(scores);
    }

    void draw()
    {

        SDL_Rect backGround;

        backGround.x = 0;
        backGround.y = 0;
        backGround.w = 600;
        backGround.h = 600;

        SDL_SetRenderDrawColor(
        this->m_renderer.get(),
        20,
        20,
        20,
        255);

        SDL_RenderFillRect(this->m_renderer.get(), &backGround);



        m_graph.draw(this->m_renderer.get());

        SDL_RenderPresent(this->m_renderer.get());
    }

    void clear()
    {
        SDL_RenderClear(this->m_renderer.get());
    }
};