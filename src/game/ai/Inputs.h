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

    float getDistance(float x1, float y1, float x2, float y2);
    float getStandardDistance(float x1, float y1, float x2, float y2);

    float getStandardAngle(float x1, float y1, float x2, float y2);
    float standardizeMomentum(int32_t value);

public:
    const static uint32_t count = 4;

    Inputs(std::shared_ptr<Frame> frame);

    ~Inputs();

    std::vector<float> generateInputs();
};