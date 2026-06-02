#include "iostream"
#include "Node.h"
#include "Resistor.h"
#include "VoltageSource.h"
#include "Circuit.h"

int main() {
    std::cout << "\n---Simulation Build---\n";

    // Create a circuit manager for your simulation
    Circuit Circuit001;

    // Create the nodes
    // Note: The 'new' keyword is used for creating a permanent address for an object which can not be deleted unless explicitly
    Node* ground = new Node(0);
    Node* nodeA = new Node(1);
    Node* nodeB = new Node(2);
    Node* nodeC = new Node(3);

    // Add the nodes to the circuit manager
    Circuit001.addNode(ground);
    Circuit001.addNode(nodeA);
    Circuit001.addNode(nodeB);
    Circuit001.addNode(nodeC);

    // Create the circuit components
    Component* R1 = new Resistor("R1", ground, nodeA, 20.85);
    Component* R2 = new Resistor("R2", nodeA, ground, 15.00);
    Component* R3 = new Resistor("R3", nodeA, nodeB, 7.53);
    Component* R4 = new Resistor("R4", nodeB, ground, 14.60);
    Component* R5 = new Resistor("R5", nodeB, ground, 33.41);
    Component* V1 = new VoltageSource("V1", ground, nodeA, 40.00);

    // Add the components to the ciruit manager
    Circuit001.addComponent(R1);
    Circuit001.addComponent(R2);
    Circuit001.addComponent(R3);
    Circuit001.addComponent(R4);
    Circuit001.addComponent(R5);
    Circuit001.addComponent(V1);

    // Execution of the simulation
    Circuit001.buildAdmittanceMatrix();
    Circuit001.findNodeVolatge();
    Circuit001.findMeshCurrent();
    Circuit001.printResult();

    return 0;
};