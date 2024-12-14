#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <string>
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

public:
    ModelStats(
        uint32_t *evolution,
        std::vector<float> *scores);

    ~ModelStats();
    void useScoreVector(std::vector<float> *scores);
    void draw();
    void clear();

private: 
    void displayText(
        std::string str,
        int32_t x,
        int32_t y,
        TTF_Font *font,
        HAlignment alignX = HAlignment::LEFT,
        VAlignment alignY = VAlignment::TOP);

    std::string makeFloatStatString(
        std::string preText, 
        float value, 
        int totalWidth = 20, 
        int valueWidth = 10,
        int precuision = 3
    );
};