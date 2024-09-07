#pragma once

#include <string>
#include <vector>

#include "layer/Layer.h"
/*
A neural network is a computational model inspired by the way biological neural networks in the human brain work. It's designed to recognize patterns, learn from data, and make decisions or predictions. Here’s a simplified explanation of how a neural network operates:

Components of a Neural Network

Neurons:

The basic unit of a neural network is a neuron (or node). Each neuron receives input, processes it, and produces an output. Neurons are organized into layers.

Layers:

Input Layer: The first layer that receives the initial data. Each neuron in this layer represents a feature or input variable of the data.
Hidden Layers: These layers lie between the input and output layers. They are called "hidden" because they are not directly exposed to the outside world. They perform various computations and feature extraction. A neural network can have one or more hidden layers.
Output Layer: The final layer that produces the output of the network. It represents the final prediction or classification result.

Weights:

Connections between neurons are represented by weights. Each connection has a weight that adjusts during training. These weights determine the strength and direction of the influence one neuron has on another.

Activation Function:

Each neuron applies an activation function to the weighted sum of its inputs. The activation function introduces non-linearity into the network, allowing it to learn and represent more complex relationships in the data. Common activation functions include ReLU (Rectified Linear Unit), Sigmoid, and Tanh.


How It Works

Forward Propagation:

Input: Data is fed into the input layer.
Processing: For each neuron in a layer, the network calculates the weighted sum of inputs, adds a bias term, and then applies the activation function to produce the neuron's output.
Propagation: The outputs from one layer become the inputs for the next layer. This process continues through all layers until the output layer is reached.

Loss Calculation:

After forward propagation, the network's output is compared to the actual target values. The difference between the predicted output and the actual target is measured using a loss function (such as Mean Squared Error for regression or Cross-Entropy Loss for classification).

Backpropagation:

Error Calculation: The loss function calculates the error, or the amount by which the network’s prediction deviates from the actual value.
Gradient Computation: The network computes gradients of the loss function with respect to each weight using the chain rule of calculus. This process is known as backpropagation.
Weight Update: Using the gradients, the network updates the weights and biases to minimize the loss. This is typically done using optimization algorithms like Gradient Descent or its variants (e.g., Adam, RMSprop).
Iteration:

Steps 1 through 3 are repeated for many iterations (epochs) over the training data. With each iteration, the network adjusts its weights to reduce the error and improve its predictions.

Inference:

Once the network is trained, it can be used to make predictions on new, unseen data. The input is fed through the network via forward propagation, and the output is produced.


Summary
Neurons: Basic units that process input data.
Layers: Structured groups of neurons (input, hidden, and output).
Weights: Parameters that adjust during training to minimize error.
Activation Function: Introduces non-linearity, allowing the network to model complex functions.
Forward Propagation: Data moves through the network to generate predictions.
Backpropagation: Adjusts weights based on errors to improve accuracy.
Training and Inference: The network learns from data and makes predictions.
Neural networks are powerful tools for tasks like image recognition, natural language processing, and more, thanks to their ability to learn complex patterns and representations from data.

*/

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
        int32_t outputNodeCount
    );
    NeuralNetwork(std::string networkFileName);
    ~NeuralNetwork();

    NeuralNetwork& operator=(const NeuralNetwork& other);

    void load();
    void save();

    void evolve();

    std::vector<float> run(std::vector<float> input);

    std::shared_ptr<Layer> getLikedListLayers() {
        return this->m_layerLinkedList;
    }
};

NeuralNetwork::NeuralNetwork(
    int32_t inputNodeCount,
    int32_t layerNodeCount,
    int32_t layerCount,
    int32_t outputNodeCount
)
    : m_layerLinkedList(std::make_shared<Layer>(outputNodeCount))
{
    for (int i = 0; i < layerCount; i++) {
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

NeuralNetwork& NeuralNetwork::operator=(const NeuralNetwork& other) {
    if (this == &other)
        return *this;

    std::shared_ptr<Layer> thisStartLayer = this->m_layerLinkedList;
    std::shared_ptr<Layer> otherStartLayer = other.m_layerLinkedList;

    do {
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

void NeuralNetwork::evolve() {
    this->m_layerLinkedList->evolve();
}

std::vector<float> NeuralNetwork::run(std::vector<float> inputs) {

    this->m_layerLinkedList->setNodeValues(inputs);

    return this->m_layerLinkedList->run();
}


