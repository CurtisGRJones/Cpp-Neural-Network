#pragma once

#include <cstdlib>

class Node
{
private:
    float m_value = 0;
    float standardize(float x);
public:
    Node();
    ~Node();

    void setValue(float x);
    float getValue();
};
