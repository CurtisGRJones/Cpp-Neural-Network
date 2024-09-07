#include <SDL2/SDL.h>
#include <cmath>
#include <vector>

#include "../frame/Frame.h"

class Inputs
{
private:
    std::shared_ptr<Frame> m_frame;
    SDL_Rect *m_playerRect;

    int32_t *m_playerMU;
    int32_t *m_playerMR;

    SDL_Rect *m_targetRect;

    // TODO make this scaliable, hence why ptrs rn
    uint32_t *m_windowHeight = new uint32_t(600);
    uint32_t *m_windowWidth = new uint32_t(600);

    float getDistance(float x1, float y1, float x2, float y2)
    {
        const float dx = x1 - x2;
        const float dy = y1 - y2;

        return std::sqrt(dx * dx + dy * dy);
    }

    float getStandardDistance(float x1, float y1, float x2, float y2)
    {
        const float longest = getDistance(0, 0, float(*this->m_windowWidth), float(*this->m_windowHeight));
        return getDistance(x1, y1, x2, y2) / longest;
    }

    float getStandardAngle(float x1, float y1, float x2, float y2)
    {
        const float dx = x1 - x2;
        const float dy = y1 - y2;
        const float angle = std::atan2(dx,  dy);

        float unitAngle = angle / M_PI;

        return unitAngle;
    }

    float standardizeMomentum(int32_t value)
    {
        return float(value) / 10.0f;
    }

public:
    const static uint32_t count = 4;

    Inputs(std::shared_ptr<Frame> frame)
        : m_frame(frame),
          m_playerRect(this->m_frame->getPlayer()->getRect()),
          m_playerMU(this->m_frame->getPlayer()->getMU()),
          m_playerMR(this->m_frame->getPlayer()->getMR()),
          m_targetRect(this->m_frame->getTarget()->getRect())
    {
    }

    ~Inputs() {
        delete m_windowHeight;
        delete m_windowWidth;
    }

    std::vector<float> generateInputs()
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
};