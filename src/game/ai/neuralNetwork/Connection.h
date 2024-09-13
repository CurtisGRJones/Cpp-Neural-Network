#pragma once

#include "Node.h"

class Connection
{
private:
    float m_weight;
    bool m_enabled;
    Node *m_iNode;
    Node *m_oNode;

    float getRandomInRange(float min, float max);

public:
    Connection(Node *iNode, Node *oNode);
    ~Connection();

    void activate();
};

Connection::Connection(Node *iNode, Node *oNode)
    : m_iNode(iNode), 
      m_oNode(oNode), 
      m_weight(getRandomInRange(-1.0f, 1.0f)),
      m_enabled(true)
{
}

Connection::~Connection()
{
}

float Connection::getRandomInRange(float min, float max)
{
    return (float(std::rand()) / RAND_MAX) * (max - min) + min;
}

void Connection::activate()
{
    this->m_oNode->setValue(this->m_iNode->getValue());
}
