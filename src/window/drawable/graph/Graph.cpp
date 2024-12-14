#include "Graph.h"

#include <algorithm>
#include <iostream>

void Graph::drawFromVector(Window *window, std::vector<float> *values, SDL_Rect rect, uint32_t fgColor, uint32_t bgColour)
{
    if (values == nullptr)
    {
        return;
    }

    window->drawFullRect(&rect, bgColour);

    window->useColorWrapper(
        fgColor,
        [window, values, &rect]()
        {
            int pointCount = values->size();
            
            // TODO make padding configurable
            int hPadding = 0.05 * rect.w;
            int hWrittable = rect.w - 2*hPadding;

            int vPadding = 0.05 * rect.h;
            int vWrittable = rect.h - 2*vPadding;

            int bottom = rect.y + rect.h - vPadding;
            int left = rect.x + hPadding;
            

            float hSpacing = pointCount > 1 ? hWrittable / float(pointCount - 1) : hWrittable / 2;

            float maxVal = *(std::max_element(values->begin(), values->end()));

            float vSpacing =
                maxVal == 0 ? float(vWrittable) / 2 : vSpacing = float(vWrittable) / maxVal;

            for (int i = 0; i < pointCount; i++)
            {
                int x = int(left + i * hSpacing);
                int y = int(bottom - values->at(i) * vSpacing);

                window->drawPoint(x, y);
            }
        });
}