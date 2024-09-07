#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(
    int32_t inputNodeCount,
    int32_t layerNodeCount,
    int32_t layerCount,
    int32_t outputNodeCount)
    : m_layerLinkedList(std::make_shared<Layer>(outputNodeCount))
{
    for (int i = 0; i < layerCount; i++)
    {
        this->m_layerLinkedList = std::make_shared<Layer>(layerNodeCount, this->m_layerLinkedList);
    }

    this->m_layerLinkedList = std::make_shared<Layer>(inputNodeCount, m_layerLinkedList);
}

NeuralNetwork::NeuralNetwork(std::string networkFileName)
    : m_networkFileName(networkFileName)
{
    this->load();
}

NeuralNetwork::~NeuralNetwork()
{
}

NeuralNetwork &NeuralNetwork::operator=(const NeuralNetwork &other)
{
    if (this == &other)
        return *this;

    std::shared_ptr<Layer> thisStartLayer = this->m_layerLinkedList;
    std::shared_ptr<Layer> otherStartLayer = other.m_layerLinkedList;

    do
    {
        *thisStartLayer = *otherStartLayer;
        thisStartLayer = thisStartLayer->getNextLayer();
        otherStartLayer = otherStartLayer->getNextLayer();
    } while (thisStartLayer);

    return *this;
}

void NeuralNetwork::save()
{
}

void NeuralNetwork::load()
{
}

void NeuralNetwork::evolve()
{
    this->m_layerLinkedList->evolve();
}

std::vector<float> NeuralNetwork::run(std::vector<float> inputs)
{

    this->m_layerLinkedList->setNodeValues(inputs);

    return this->m_layerLinkedList->run();
}

std::shared_ptr<Layer> NeuralNetwork::getLikedListLayers()
{
    return this->m_layerLinkedList;
}
