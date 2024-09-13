#include "Inputs.h"

Inputs::Inputs(std::shared_ptr<Frame> frame)
    : m_frame(frame),
      m_playerRect(this->m_frame->getPlayer()->getRect()),
      m_playerMU(this->m_frame->getPlayer()->getMU()),
      m_playerMR(this->m_frame->getPlayer()->getMR()),
      m_targetRect(this->m_frame->getTarget()->getRect())
{
}

Inputs::~Inputs()
{
    delete m_windowHeight;
    delete m_windowWidth;
}

float Inputs::getDistance(float x1, float y1, float x2, float y2)
{
    const float dx = x1 - x2;
    const float dy = y1 - y2;

    return std::sqrt(dx * dx + dy * dy);
}

float Inputs::getStandardDistance(float x1, float y1, float x2, float y2)
{
    const float longest = this->getDistance(0, 0, float(*this->m_windowWidth), float(*this->m_windowHeight));
    return this->getDistance(x1, y1, x2, y2) / longest;
}

float Inputs::getStandardAngle(float x1, float y1, float x2, float y2)
{
    const float dx = x1 - x2;
    const float dy = y1 - y2;
    const float angle = std::atan2(dx, dy);

    float unitAngle = angle / M_PI;

    return unitAngle;
}

float Inputs::standardizeMomentum(int32_t value)
{
    return float(value) / 10.0f;
}

std::vector<float> Inputs::generateInputs()
{
    std::vector<float> retVec = {
        this->getStandardDistance(
            this->m_playerRect->x,
            this->m_playerRect->y,
            this->m_targetRect->x,
            this->m_targetRect->y),
        this->getStandardAngle(
            this->m_playerRect->x,
            this->m_playerRect->y,
            this->m_targetRect->x,
            this->m_targetRect->y),
        standardizeMomentum(*this->m_playerMU),
        standardizeMomentum(*this->m_playerMR),
    };
    return retVec;
}