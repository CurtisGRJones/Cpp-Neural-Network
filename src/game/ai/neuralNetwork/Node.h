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

Node::Node()
{
}

Node::~Node()
{
}

float Node::standardize(float x)
{
    return x / (1 + std::abs(x));
}

void Node::setValue(float x)
{
    this->m_value = this->standardize(x);
}

float Node::getValue()
{
    return this->m_value;
}
