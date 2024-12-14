#include "StatsWindow.h"

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <numeric>

ModelStats::ModelStats(
    uint32_t *evolution,
    std::vector<float> *scores)
    : m_evolution(evolution),
      m_scores(scores),
      m_graph(Graph())
{
    m_defaultFont.reset(TTF_OpenFont(this->m_defaultFontPath.c_str(), 24));

    if (this->m_defaultFont == nullptr)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        this->m_window.destroy();
        TTF_Quit();
        SDL_Quit();
        return;
    }
}

ModelStats::~ModelStats()
{
}

void ModelStats::useScoreVector(std::vector<float> *scores)
{
    this->m_scores = scores;
}

void ModelStats::draw()
{
    this->m_window.fillBackground(0x202020FF);

    this->m_graph.drawFromVector(&(this->m_window), this->m_scores, SDL_Rect{0, 100, 600, 300}, 0xFF0000FF);

    this->m_window.displayText("Generation", 300, 10, this->m_defaultFont.get(), HAlignment::CENTER);
    std::string strEvolution = std::to_string(*(this->m_evolution));
    this->m_window.displayText(strEvolution, 300, 40, this->m_defaultFont.get(), HAlignment::CENTER);

    // TODO add ability for display text to run multiple lines

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

    float average = std::accumulate(this->m_scores->begin(), this->m_scores->end(), 0.0f) / n;

    const int statWidth = 200;

    this->drawStat(
        "Last:",
        this->m_scores->front(),
        50,
        500,
        statWidth,
        HAlignment::LEFT
    );

    this->drawStat(
        "First:",
        this->m_scores->back(),
        550,
        500,
        statWidth,
        HAlignment::RIGHT
    );

    this->drawStat(
        "Median:",
        median,
        50,
        550,
        statWidth,
        HAlignment::LEFT
    );

    this->drawStat(
        "Average:",
        average,
        550,
        550,
        statWidth,
        HAlignment::RIGHT
    );

    this->m_window.pushRenderToWindow();
}

void ModelStats::clear()
{
    this->m_window.clear();
}

std::string ModelStats::makeFloatString(
    float value,
    int precuision)
{
    std::ostringstream oss;
    oss << std::setprecision(precuision)
        << value;
    return oss.str();
}

void ModelStats::drawStat(
    std::string statName,
    float statVal,
    uint32_t x,
    uint32_t y,
    uint32_t w,
    HAlignment hAlignment,
    VAlignment vAlignment)
{

    std::string stratValStr = this->makeFloatString(statVal);

    switch (hAlignment)
    {
    case HAlignment::RIGHT:
        x -= w;
        break;
    case HAlignment::CENTER:
        x-= w/2;
        break;
    }

    this->m_window.displayText(
        statName,
        x,
        y,
        this->m_defaultFont.get(),
        HAlignment::LEFT,
        vAlignment);

    this->m_window.displayText(
        this->makeFloatString(statVal),
        x + w,
        y,
        this->m_defaultFont.get(),
        HAlignment::RIGHT,
        vAlignment);
}
