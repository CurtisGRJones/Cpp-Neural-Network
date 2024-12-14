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
    std::string makeFloatStatString(
        std::string preText, 
        float value, 
        int totalWidth = 20, 
        int valueWidth = 10,
        int precuision = 3
    );
};