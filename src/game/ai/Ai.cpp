#include "Ai.h"

Ai::Ai()
    : m_frame(std::make_shared<Frame>(Frame())),
      m_inputs(this->m_frame),
      m_id(Ai::idIttr),
      m_familyId(this->m_id)
{
    Ai::idIttr++;
}

Ai::Ai(std::shared_ptr<Frame> frame)
    : m_frame(frame),
      m_inputs(this->m_frame),
      m_id(Ai::idIttr),
      m_familyId(this->m_id)
{
    Ai::idIttr++;
}

Ai::~Ai()
{
}

Ai &Ai::operator=(const Ai &other)
{
    if (this == &other)
        return *this;

    this->m_nn = other.m_nn;

    this->m_familyId = other.m_familyId;

    return *this;
}

uint32_t Ai::idIttr = 0;

void Ai::tick()
{
    std::vector<float> inputs = this->m_inputs.generateInputs();

    std::vector<float> results = this->m_nn.run(inputs);

    float maxScore = -INFINITY;
    uint32_t index = 0;

    for (int i = 0; i < results.size(); i++)
    {
        if (results.at(i) > maxScore)
        {
            index = i;
            maxScore = results.at(i);
        }
    }

    if (index < 4)
    {
        this->m_frame->getPlayer()->changeMomentumByDirection(index);
    }
}

std::shared_ptr<Frame> Ai::getFrame()
{
    return this->m_frame;
}

float Ai::calcScore()
{
    this->m_score = this->m_frame->getPlayer()->getPoints();

    SDL_Rect *playerRect = this->m_frame->getPlayer()->getRect();
    SDL_Rect *targetRect = this->m_frame->getTarget()->getRect();

    int32_t dx = playerRect->x - targetRect->x;
    int32_t dy = playerRect->y - targetRect->y;

    float screenDiagonal = std::sqrt(2.0f) * 600.0f;

    this->m_score += (screenDiagonal - std::sqrt(float(dx * dx + dy * dy))) / (screenDiagonal / 0.5f);

    return this->m_score;
}

float Ai::getScore()
{
    return this->m_score;
}

void Ai::evolve()
{
    this->m_nn.evolve();
}

uint32_t Ai::getId()
{
    return this->m_id;
}
uint32_t Ai::getFamilyId()
{
    return this->m_familyId;
}

NeuralNetwork *Ai::getNeuralNetwork()
{
    return &this->m_nn;
}

Inputs *Ai::getInputs()
{
    return &this->m_inputs;
}