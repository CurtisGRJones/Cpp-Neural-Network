#pragma once

#include <string>
#include <vector>

#include "layer/Layer.h"

class NeuralNetwork
{
private:
    std::string m_networkFileName;

    std::shared_ptr<Layer> m_layerLinkedList;

public:
    NeuralNetwork(
        int32_t inputNodeCount,
        int32_t layerNodeCount,
        int32_t layerCount,
        int32_t outputNodeCount);
    NeuralNetwork(std::string networkFileName);
    ~NeuralNetwork();

    NeuralNetwork &operator=(const NeuralNetwork &other);

    void load();
    void save();

    void evolve();

    std::vector<float> run(std::vector<float> input);

    std::shared_ptr<Layer> getLikedListLayers();
};