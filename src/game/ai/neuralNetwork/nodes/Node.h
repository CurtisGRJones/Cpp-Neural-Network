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

Node::Node(uint32_t nextLayerWidth)
    : m_bias(this->getRandomInRange(-0.1f, 0.1f))
{
    this->m_weights.reserve(nextLayerWidth);

    for (int i = 0; i < nextLayerWidth; i++)
    {
        this->m_weights.push_back(this->getRandomInRange(-1.0f, 1.0f));
    }
}

Node::Node(std::vector<float> weights, float bias)
    : m_bias(bias)
{
    this->m_weights.reserve(weights.size());
    this->m_weights = weights;
}

Node::~Node()
{
}

Node &Node::operator=(const Node &other)
{
    if (this == &other)
        return *this;

    std::copy(other.m_weights.begin(), other.m_weights.end(), this->m_weights.begin());

    this->m_bias = other.m_bias;
    return *this;
}

float Node::standardize(float x)
{
    return x / (1 + std::abs(x));
}

float Node::getRandomInRange(float min, float max)
{
    return (float(std::rand()) / RAND_MAX) * (max - min) + min;
}

std::vector<float> *Node::getWeights()
{
    return &this->m_weights;
}

void Node::setWeights(std::vector<float> *weights)
{
    std::copy(weights->begin(), weights->end(), this->m_weights.begin());
}

float Node::getBias()
{
    return this->m_bias;
}

void Node::setBias(float bias)
{
    this->m_bias = bias;
}

void Node::setValue(float x)
{
    this->m_value = this->standardize(x);
}

float Node::getValue()
{
    return this->m_value;
}

std::vector<float> Node::activate()
{
    std::vector<float> results;
    results.reserve(this->m_weights.size());

    for (const auto &weight : this->m_weights)
    {
        results.push_back(this->standardize(this->m_value * weight) + this->m_bias);
    }

    return results;
}

void Node::evolve()
{

    uint32_t toRandomize = std::rand() % (this->m_weights.size() + 1);

    if (toRandomize = this->m_weights.size())
    {
        this->m_bias += this->getRandomInRange(-0.01f, 0.01f);
    } else {
        this->m_weights[toRandomize] += this->getRandomInRange(-0.1f, 0.1f);
    }
}