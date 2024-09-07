#pragma once

#include <vector>
#include <cstdlib>
#include <random>
#include <stdexcept>

class Node
{
private:
    float m_value = 0;

    std::vector<float> m_weights;
    float m_bias;

private:
    float standardize(float x);

    float getRandomInRange(float min, float max);

public:
    Node(uint32_t nextLayerWidth);
    Node(std::vector<float> weights, float bias);
    ~Node();
    Node &operator=(const Node &other);

    std::vector<float> *getWeights();
    void setWeights(std::vector<float> *weights);
    float getBias();
    void setBias(float bias);

    void setValue(float x);
    float getValue();

    std::vector<float> activate();

    void evolve();
};