#include "iostream"
#include "Node.h"
#include "Resistor.h"
#include "VoltageSource.h"
#include "CurrentSource.h"
#include "Circuit.h"

int main() {
    std::cout << "\n--- Simulation Build In Process ---\n";

    // Create a circuit manager for your simulation
    Circuit Circuit001;

    // Create the nodes
    // Note: The 'new' keyword is used for creating a permanent address for an object which can not be deleted unless explicitly
    Node* ground = new Node(0);
    Node* nodeA = new Node(1);
    Node* nodeB = new Node(2);
    Node* nodeC = new Node(3);
    Node* nodeD = new Node(4);

    // Add the nodes to the circuit manager
    Circuit001.addNode(ground);
    Circuit001.addNode(nodeA);
    Circuit001.addNode(nodeB);
    Circuit001.addNode(nodeC);
    Circuit001.addNode(nodeD);

    // Create the circuit components
    Component* R1 = new Resistor("Resistor R1", nodeA, nodeB, 5);
    Component* R2 = new Resistor("Resistor R2", nodeC, nodeB, 10);
    Component* R3 = new Resistor("Resistor R3", nodeB, nodeD, 6);
    Component* R4 = new Resistor("Resistor R4", nodeD, ground, 4);
    Component* V1 = new VoltageSource("V1", ground, nodeA, 15.00);
    Component* V2 = new VoltageSource("V2", ground, nodeC, 10.00);

    // Add the components to the ciruit manager
    Circuit001.addComponent(R1);
    Circuit001.addComponent(R2);
    Circuit001.addComponent(R3);
    Circuit001.addComponent(R4);
    Circuit001.addComponent(V1);
    Circuit001.addComponent(V2);

    
    // Execution of the simulation
    Circuit001.buildAdmittanceMatrix();
    Circuit001.buildImpedanceMatrix();
    Circuit001.findSolutions();
    Circuit001.printResult();

    // Build Successful
    std::cout << "\n--- Simulation Build Successful ---\n";

    return 0;
};