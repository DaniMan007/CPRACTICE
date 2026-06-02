#include "Resistor.h"
#include "iostream"

// Building the constructor
Resistor::Resistor(std::string compName, Node* n01, Node* n02, float resistance): 
    Component(compName, n01, n02, resistance) {};

// Defining the getter
float Resistor::getConductance() const {
    // To ensure we encounter no errors
    if(value == 0.0) return 1e20; 

    // If no errors will be encountered:
    return 1 / value;
};
/// @brief Gets the resistance of the resistor
/// @return The resistance value
float Resistor::getResistance() const {
    return value;
}

// The print function
void Resistor::PrintOut() const {
    // Calling the base class to print out the basic details
    Component::PrintOut();

    // Adding extra component information
    std::cout << ", Resistance is: " << value << " Ohms" << std::endl;
};