#pragma once

#include <memory>
#include <random>

#include "../nodes/Node.h"

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

    std::vector<Node> *getNodes();
};