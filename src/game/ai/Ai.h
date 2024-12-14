#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "Inputs.h"
#include "neuralNetwork/NeuralNetwork.h"
#include "../frame/Frame.h"

class Ai
{
private:
    NeuralNetwork m_nn = NeuralNetwork(
        Inputs::count,
        10,
        10,
        5);

    std::shared_ptr<Frame> m_frame;

    Inputs m_inputs;

    float m_score = 0;

    static uint32_t idIttr;

    const uint32_t m_id;
    uint32_t m_familyId;

public:
    Ai();
    Ai(std::shared_ptr<Frame> frame);
    ~Ai();

    Ai &operator=(const Ai &other);

    void tick();
    std::shared_ptr<Frame> getFrame();

    float calcScore();
    float getScore();

    void evolve();

    uint32_t getId();
    uint32_t getFamilyId();

    NeuralNetwork *getNeuralNetwork();

    Inputs *getInputs();
};
