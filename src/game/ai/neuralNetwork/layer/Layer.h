#pragma once

#include "../nodes/Node.h"

#include <random>

class Layer
{
private:
    std::shared_ptr<Layer> m_next;
    std::vector<Node> m_nodes;
    uint32_t m_width;

public:
    Layer(uint32_t layerWidth, std::shared_ptr<Layer> next = nullptr);
    Layer(std::vector<std::vector<float>> weights, std::vector<float> bias, std::shared_ptr<Layer> next = nullptr);
    ~Layer();

    Layer& operator=(const Layer& other);

    uint32_t getWidth();

    void setNodeValues(std::vector<float> values);
    std::vector<float> getNodeValues();

    std::shared_ptr<Layer> getNextLayer();

    std::vector<float> run();
    void evolve();

    std::vector<Node> *getNodes() {
        return &this->m_nodes;
    }
};

Layer::Layer(uint32_t layerWidth, std::shared_ptr<Layer> next)
    : m_width(layerWidth),
      m_next(next)
{
    uint32_t nextLayerWidth = this->m_next ? this->m_next->getWidth() : 1;
    this->m_nodes.reserve(this->m_width);
    for (uint32_t i = 0; i < this->m_width; i++)
    {
        m_nodes.push_back(Node(nextLayerWidth));
    }
}

Layer::Layer(std::vector<std::vector<float>> weights, std::vector<float> bias, std::shared_ptr<Layer> next)
    : m_width(weights.size()),
      m_next(next)
{
    if (bias.size() != this->m_width)
    {
        throw std::runtime_error("bias length does not match current layer size");
    }

    this->m_nodes.reserve(this->m_width);

    uint32_t nextLayerWidth = this->m_next ? this->m_next->getWidth() : 1;

    for (uint32_t i = 0; i < this->m_width; i++)
    {
        if (weights.at(i).size() != nextLayerWidth)
        {
            throw std::runtime_error("weight length does not match next layer size");
        }
        m_nodes.push_back(Node(weights.at(i), bias.at(i)));
    }
}

Layer::~Layer()
{
}

Layer& Layer::operator=(const Layer& other) {
    if (this == &other)
        return *this;

    std::copy(other.m_nodes.begin(), other.m_nodes.end(), this->m_nodes.begin());

    this->m_width = other.m_width;
    return *this;
}

uint32_t Layer::getWidth()
{
    return this->m_width;
}

void Layer::setNodeValues(std::vector<float> values)
{
    if (values.size() != this->m_width)
    {
        throw std::runtime_error("Value size does not match layer width");
    }

    for (int i = 0; i < values.size(); i++)
    {
        this->m_nodes[i].setValue(values.at(i));
    }
}

std::shared_ptr<Layer> Layer::getNextLayer() {
    return this->m_next;
}

std::vector<float> Layer::getNodeValues()
{
    std::vector<float> result;

    result.reserve(this->m_nodes.size());

    for (auto &node : this->m_nodes)
    {
        result.push_back(node.getValue());
    }

    return result;
}

std::vector<float> Layer::run()
{
    if (!this->m_next)
    {
        return this->getNodeValues();
    }

    std::vector<float> newNodeValues(this->m_next->getWidth(), 0);
    std::vector<float> adderValues;

    for (auto &node : this->m_nodes)
    {
        adderValues = node.activate();
        for (int i = 0; i < adderValues.size(); i++)
        {
            newNodeValues[i] += adderValues[i];
        }
    }

    this->m_next->setNodeValues(newNodeValues);

    return this->m_next->run();
}

void Layer::evolve()
{
    for (auto &node : this->m_nodes)
    {
        node.evolve();
    }

    if( this->m_next ) {
        this->m_next->evolve();
    }
}
