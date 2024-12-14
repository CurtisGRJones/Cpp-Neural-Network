#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <numeric>
#include <filesystem>
namespace fs = std::filesystem;

#include "graph/graph.h"

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

class ModelStats
{
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    Graph m_graph;

    uint32_t *m_evolution;
    std::vector<float> *m_scores;
    fs::path m_defaultFontPath = std::filesystem::current_path() / "assets" / "fonts" / "Roboto-Black.ttf";
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_defaultFont = {nullptr, &TTF_CloseFont};

    void displayText(
        std::string str,
        int32_t x,
        int32_t y,
        TTF_Font *font,
        // TODO change these to an int "align" flag
        HAlignment alignX = HAlignment::LEFT,
        VAlignment alignY = VAlignment::TOP)
    {
        if (this->m_evolution != nullptr)
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
    }

    std::string makeFloatStatString(
        std::string preText, 
        float value, 
        int totalWidth = 20, 
        int valueWidth = 10,
        int precuision = 3
    ) {
        std::ostringstream oss;
        oss << std::left        
            << std::setw(totalWidth - valueWidth)
            << preText
            << std::fixed
            << std::setprecision(precuision)
            << std::setw(valueWidth)
            << std::right
            << value;
        return oss.str();
    }

public:
    ModelStats(
        uint32_t *evolution,
        std::vector<float> *scores)
        : m_window(nullptr, SDL_DestroyWindow),
          m_renderer(nullptr, SDL_DestroyRenderer),
          m_evolution(evolution),
          m_scores(scores),
          m_graph(Graph(scores))
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

        if (TTF_Init() == -1)
        {
            std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        m_defaultFont.reset(TTF_OpenFont(this->m_defaultFontPath.c_str(), 24));

        if (this->m_defaultFont == nullptr)
        {
            std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
            SDL_DestroyRenderer(this->m_renderer.get());
            SDL_DestroyWindow(this->m_window.get());
            TTF_Quit();
            SDL_Quit();
            return;
        }
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

        this->displayText("Generation", 300, 10, this->m_defaultFont.get(), HAlignment::CENTER);
        std::string strEvolution = std::to_string(*(this->m_evolution));
        this->displayText(strEvolution, 300, 40, this->m_defaultFont.get(), HAlignment::CENTER);

        // TODO place value and stat sperately for nicer formatting
        // TODO add ability for display text to run multiple lines
        this->displayText(
            this->makeFloatStatString("Last:", this->m_scores->front()),
            50,
            500,
            this->m_defaultFont.get(),
            HAlignment::LEFT,
            VAlignment::TOP);

        this->displayText(
            this->makeFloatStatString("First:", this->m_scores->back()),
            550,
            500,
            this->m_defaultFont.get(),
            HAlignment::RIGHT,
            VAlignment::TOP);

        size_t n = this->m_scores->size();
        float median;
        if (n % 2 != 0)
        {
            median = this->m_scores->at(n / 2);
        }
        else
        {
            median = (this->m_scores->at(n / 2 - 1) + this->m_scores->at(n / 2)) / 2.0;
        }
        this->displayText(
            this->makeFloatStatString("Median:", median),
            50,
            550,
            this->m_defaultFont.get(),
            HAlignment::LEFT,
            VAlignment::TOP);

        
        float average = std::accumulate(this->m_scores->begin(), this->m_scores->end(), 0.0f) / n;

        this->displayText(
            this->makeFloatStatString("Average:", average),
            550,
            550,
            this->m_defaultFont.get(),
            HAlignment::RIGHT,
            VAlignment::TOP);

        SDL_RenderPresent(this->m_renderer.get());
    }

    void clear()
    {
        SDL_RenderClear(this->m_renderer.get());
    }
};