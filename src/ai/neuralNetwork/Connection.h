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