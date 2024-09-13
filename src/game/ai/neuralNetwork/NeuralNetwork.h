#pragma once

#include <string>
#include <vector>

#include "Node.h"
#include "Connection.h"

class NeuralNetwork
{
private:
    std::string m_networkFileName;

    std::vector<Node> m_nodes;
    std::vector<Connection> m_connections;

public:
    NeuralNetwork(
        int32_t inputNodeCount,
        int32_t outputNodeCount);
    NeuralNetwork(std::string networkFileName);
    ~NeuralNetwork();

    NeuralNetwork &operator=(const NeuralNetwork &other);

    void load();
    void save();

    void evolve();

    void activate(std::vector<float> input);
};