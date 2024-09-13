#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(
    int32_t inputNodeCount,
    int32_t outputNodeCount)
{
    
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

    // TODO duplicate nodes and connections here

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
    
}

void NeuralNetwork::activate(std::vector<float> inputs)
{
    // set input node values;

    for ( auto connection : this->m_connections ) {
        connection.activate();
    }
}
