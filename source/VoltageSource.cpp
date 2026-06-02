#include "VoltageSource.h"
#include "iostream"

// Once again...the constructor
VoltageSource::VoltageSource(std::string compName, Node* n01, Node* n02, float voltage):
    Component(compName, n01, n02, voltage) {};

// Defining the getter
float VoltageSource::getConductance() const {
    // An ideal voltage source has zero resistance
    return 1e20;
};

// The print function
void VoltageSource::PrintOut() const {
    // Calling the base class to print out the basic details
    Component:PrintOut();

    // Adding extra component information
    std::cout << "Voltage is: " << value << " Volts\n";
};