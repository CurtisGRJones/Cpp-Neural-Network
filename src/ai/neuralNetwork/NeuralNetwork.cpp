#include "NeuralNetwork.h"
#include <stdexcept>

NeuralNetwork::NeuralNetwork(
    int32_t inputNodeCount,
    int32_t outputNodeCount)
{
    for (int i = 0; i < inputNodeCount; i++)
    {
        this->m_nodes.push_back(Node());
        this->m_inputNodes.push_back(&m_nodes.back());
    }

    for (int i = 0; i < outputNodeCount; i++)
    {
        this->m_nodes.push_back(Node());
        this->m_outputNodes.push_back(&m_nodes.back());
    }

    if (outputNodeCount > inputNodeCount)
    {
        for (int i = 0; i < outputNodeCount; i++)
        {
            this->m_connections.push_back(Connection(
                this->m_inputNodes.at(std::rand() % inputNodeCount), 
                this->m_outputNodes.at(i)
            ));
        }
    }
    else
    {
        for (int i = 0; i < inputNodeCount; i++)
        {
            this->m_connections.push_back(Connection(
                this->m_inputNodes.at(i), 
                this->m_outputNodes.at(std::rand() % outputNodeCount)
            ));
        }
    }
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

std::vector<float> NeuralNetwork::activate(std::vector<float> inputs)
{
    if ( inputs.size() != this->m_inputNodes.size() ) {
        throw std::runtime_error("Input size mismatch");
    }

    for (auto connection : this->m_connections)
    {
        connection.activate();
    }

    std::vector<float> outputValues;
    outputValues.reserve(this->m_outputNodes.size());

    for ( int i = 0; i < this->m_outputNodes.size(); i++) {
        outputValues.push_back(this->m_outputNodes.at(i)->getValue());
    }

    return outputValues;
}
