#include "Node.h"

// The constructor comes first to initialize the variables
Node::Node(int nodeId): id(nodeId), voltage(0.0) {};

// Handles the getters from 'Node.h'
int Node::getId() const {
    return id;
};
float Node::getVoltage() const {
    return voltage;
};

// Handle the setter from 'Node.h'
void Node::setVoltage(float v) {
    voltage = v;
}