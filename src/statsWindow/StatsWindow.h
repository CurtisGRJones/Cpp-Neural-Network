#pragma once

#include <string>
#include <filesystem>
namespace fs = std::filesystem;

#include "../window/Window.h"
#include "../window/drawable/graph/Graph.h"

class ModelStats
{
private:
    Window m_window;
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
    std::string makeFloatString(
        float value, 
        int precuision = 3
    );

    void drawStat (
        std::string statName,
        float statVal,
        uint32_t x,
        uint32_t y,
        uint32_t w,
        HAlignment hAlignment,
        VAlignment vAlignment = VAlignment::TOP
    );
};