#include <iostream>
#include <iomanip>
#include <functional>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <thread>

#include "game/GameHandler.h"
#include "game/ai/Ai.h"

class TrainingThread
{
private:
    std::thread m_thread;

    std::shared_ptr<std::vector<std::shared_ptr<Ai>>> m_ais;

    std::shared_ptr<bool> m_isWaiting;
    std::shared_ptr<bool> m_doneTick;
    std::shared_ptr<bool> m_quit;

    static void trainBlock(
        std::shared_ptr<std::vector<std::shared_ptr<Ai>>> ais,
        std::shared_ptr<bool> isWaiting,
        std::shared_ptr<bool> doneTick,
        std::shared_ptr<bool> quit)
    {
        while (!*quit)
        {
            if (!*isWaiting)
            {
                *isWaiting = true;
                for (int i = 0; i < 1800 && !*quit; i++)
                {
                    for (auto &ai : *ais)
                    {
                        ai->tick();
                        ai->getFrame()->tick();
                    }
                }
                *doneTick = true;
            }
            else
            {
                SDL_Delay(10);
            }
        }
    }

public:
    TrainingThread(
        std::vector<std::shared_ptr<Ai>> ais)
        : m_isWaiting(std::make_shared<bool>(true)),
          m_doneTick(std::make_shared<bool>(false)),
          m_quit(std::make_shared<bool>(false))
    {
        this->m_ais = std::make_shared<std::vector<std::shared_ptr<Ai>>>(ais.size(), nullptr);
        std::copy(ais.begin(), ais.end(), this->m_ais->begin());
        m_thread = std::thread(
            TrainingThread::trainBlock,
            m_ais,
            m_isWaiting,
            m_doneTick,
            m_quit);
    }

    void stopThread()
    {
        *this->m_quit = true;
    }

    void tickThread()
    {
        *this->m_doneTick = false;
        *this->m_isWaiting = false;
    }

    bool isDoneTick()
    {
        return *this->m_doneTick;
    }

    void join()
    {
        *this->m_quit = true;
        this->m_thread.join();
    }
};

void sortAIsByScore(std::vector<std::shared_ptr<Ai>> &ais)
{
    std::sort(ais.begin(), ais.end(), [](std::shared_ptr<Ai> a, std::shared_ptr<Ai> b)
              { return a->getScore() < b->getScore(); });
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const uint32_t threadCount = 12;
    const uint32_t aisCount = threadCount * 500;

    uint32_t evolutions = 0;
    const uint32_t maxTicks = 600;

    std::shared_ptr<Ai> trackAi;

    std::cout << "Building AI" << std::endl;

    std::vector<std::shared_ptr<Ai>> ais;
    ais.reserve(aisCount);

    for (int i = 0; i < aisCount; i++)
    {
        ais.push_back(std::make_shared<Ai>());
    }
    trackAi = ais[0];

    std::cout << "Building Game" << std::endl;
    GameHandler game(false, ais.back()->getFrame(), false);

    std::cout << "Spawning Threads" << std::endl;
    std::vector<TrainingThread> threads;
    threads.reserve(threadCount);
    const uint32_t threadBatchCount = ais.size() / threadCount;

    for (int i = 0; i < threadCount; i++)
    {
        auto batchStart = ais.begin() + (threadBatchCount * i);
        auto batchEnd = (i == threadCount - 1) ? ais.end() : batchStart + threadBatchCount;

        if (batchEnd > ais.end())
        {
            batchEnd = ais.end();
        }

        std::vector<std::shared_ptr<Ai>> aiBatch;
        aiBatch.resize(threadBatchCount, nullptr);

        std::copy(batchStart, batchEnd, aiBatch.begin());

        threads.push_back(TrainingThread(aiBatch));
    }

    while (game.isRunning())
    {
        for (auto &thread : threads)
        {
            thread.tickThread();
        }

        for (auto &thread : threads)
        {
            while (!thread.isDoneTick() && game.isRunning())
            {
                game.draw();
                game.handleEvents();
                SDL_Delay(1);
            }
        }

        for (auto &ai : ais)
        {
            ai->calcScore();
            ai->getFrame()->reset();
        }

        sortAIsByScore(ais);

        std::cout << std::left << "Scores For Evolution " << evolutions << ": " << std::endl
                  << std::setw(8) << "First: " << std::setw(5) << ais.back()->getId()  << std::setw(5) <<  ais.back()->getFamilyId() << "-> " << ais.back()->getScore() << std::endl
                  << std::setw(8) << "Median: " << std::setw(5) << ais.at(uint32_t(aisCount / 2))->getId()  << std::setw(5) << ais.at(uint32_t(aisCount / 2))->getFamilyId() << "-> " << ais.at(uint32_t(aisCount / 2))->getScore() << std::endl
                  << std::setw(8) << "Last: " << std::setw(5) << ais.front()->getId()  << std::setw(5) << ais.front()->getFamilyId() << "-> " << ais.front()->getScore() << std::endl;

        evolutions++;
        game.changeFrame(ais.back()->getFrame());

        for (int i = 0; i < ais.size() / 2; i++)
        {
            *ais[i] = *ais[ais.size() - i - 1];

            ais[i]->evolve();
        }
    }

    std::cout << "Joining Threads" << std::endl;
    for (auto &thread : threads)
    {
        thread.join();
    }

    return 0;
}