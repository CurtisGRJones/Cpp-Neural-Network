#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

#include "game/GameHandler.h"
#include "game/ai/Ai.h"

void sortAIsByScore(std::vector<Ai*> &ais)
{
    std::sort(ais.begin(), ais.end(), [](Ai *a, Ai *b)
              { return a->getScore() < b->getScore(); });
}

// TODO thread this up
int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << "Building Game" << std::endl;

    std::cout << "Building AI" << std::endl;

    const uint32_t runnerCount = 5000;

    std::vector<Ai*> ais;
    ais.reserve(runnerCount);

    for (int i = 0; i < runnerCount; i++)
    {
        ais.push_back(new Ai());
    }

    GameHandler game(false, ais.back()->getFrame(), false);

    auto start = std::chrono::system_clock::now();

    uint32_t evolutions = 0;
    const uint32_t maxTicks = 600;

    Ai *testAi = ais[0];

    float cumulativeScore = 0.0f;

    while (game.isRunning())
    {

        for (int i = 0; i < 1000 /* std::min(maxTicks, 30 * uint32_t(1 + evolutions / 50)) */; i++)
        {

            for (auto &ai : ais)
            {
                ai->tick();
            }

            game.tick();
        }

        cumulativeScore = 0.0f;

        for (auto &ai : ais)
        {
            cumulativeScore += ai->calcScore();;
            ai->getFrame()->reset();
        }

        sortAIsByScore(ais);

        std::cout << "Scores For Evolution " << evolutions << ": " << std::endl << 
            "First: " << ais.back()->getScore() << std::endl << 
            "Averge:" << cumulativeScore / float(runnerCount) << std::endl <<
            "Last:" << ais.front()->getScore() << std::endl;

        evolutions++;
        game.changeFrame(ais.back()->getFrame());

        for ( int i = 0; i < ais.size() / 2; i++ ) {
            *ais[i] = *ais[ais.size() - i - 1];

            ais[i]->evolve();
        }
    } 

    return 0;
}