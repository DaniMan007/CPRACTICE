#include "CurrentSource.h"
#include "iostream"

// Once again...the constructor
CurrentSource::CurrentSource(std::string compName, Node* n01, Node* n02, float current):
    Component(compName, n01, n02, current) {};

// Defining the current getter
float CurrentSource::getCurrent() const {
    return value;
};

// Defining the getter
float CurrentSource::getConductance() const {
    // An ideal current source has infinite resistance
    return 0.0f;
};
/// @brief Gets the resistance of the current source
/// @return The resistance value
float CurrentSource::getResistance() const {
    // An ideal current source has infinite resistance
    return 1e20;
};

// The print function
void CurrentSource::PrintOut() const {
    // Calling the base class to print out the basic details
    Component::PrintOut();

    // Adding extra component information
    std::cout << ", Current is: " << value << " Amps" << std::endl;
};