#include "Resistor.h"
#include "Circuit.h"
#include "iostream"
#include "iomanip" // For formatting matrix output

// Building the constructor and the destructor
Circuit::Circuit() {};
Circuit::~Circuit() {
    for(int i = 0; i < nodes.size(); i++) {
        delete nodes[i];
    };

    for(int j = 0; j < components.size(); j++) {
        delete components[j];
    };
};

// Building the circuit
void Circuit::addNode(Node* node) {
    nodes.push_back(node);
};
void Circuit::addComponent(Component* component) {
    components.push_back(component);
};

// Calculation Functions
void Circuit::buildAdmittanceMatrix() {
    std::cout << "\n--- Building Y Matrix ---\n";

    int nodesNum = nodes.size();
    
    //Creating a N x N matrix filled with zeros using vectors; This is the standard way of creating dynamic arrays, matrices.
    
    // Ensure a local matrix is available if a member isn't defined
    Y_Matrix.assign(nodesNum, std::vector<float>(nodesNum, 0.0));

    // The Stamping Algorithm
    for(int k = 0; k < components.size(); k++) {
        Component* compName = components[k];

        // THE VIP BOUNCER
        // This is the part where we check if the component is a voltage source or not, if it is then we skip it because we can't use the nodal analysis method for voltage sources
        if(compName->getName()[0] == 'V') continue;

        // Getting the node ID's
        int n01 = compName->get01()->getId();
        int n02 = compName->get02()->getId();

        // Getting the conductacne
        float g = compName->getConductance();

        // This is the c++ version of the nodal analysis rule: Add conductances to the diagonal entries and subtract them from no-diagonal entries
        if (n01 != 0) Y_Matrix.at(n01).at(n01) += g;
        if (n02 != 0) Y_Matrix.at(n02).at(n02) += g;

        if(n01 != 0.0 && n02 != 0.0) {
            Y_Matrix.at(n01).at(n02) -= g;
            Y_Matrix.at(n02).at(n01) -= g;      
        };
    };

    // To verify the matrix
    for(int row = 1; row < nodesNum; row++) {
        for(int column = 1; column < nodesNum; column++) {
            std::cout << std::setw(20) << Y_Matrix.at(row).at(column);
        }
        std::cout << "\n";
    };

};
void Circuit::buildImpedanceMatrix() {
    std::cout << "\n--- Building Z Matrix ---\n";

    int nodesNum = nodes.size();
    
    //Creating a N x N matrix filled with zeros using vectors; This is the standard way of creating dynamic arrays, matrices.
    
    // Ensure a local matrix is available if a member isn't defined
    Z_Matrix.assign(nodesNum, std::vector<float>(nodesNum, 0.0));

    // The Stamping Algorithm
    for(int k = 0; k < components.size(); k++) {
        Component* compName = components[k];

        // THE VIP BOUNCER
        // This is the part where we check if the component is a current source or not, if it is then we skip it because we can't use the nodal analysis method for voltage sources
        if(compName->getName()[0] == 'I') continue;

        // Getting the node ID's
        int n01 = compName->get01()->getId();
        int n02 = compName->get02()->getId();

        // Getting the resistance
        float r = compName->getResistance();

        // This is the c++ version of the nodal analysis rule: Add resistances to the diagonal entries and subtract them from no-diagonal entries
        if (n01 != 0) Z_Matrix.at(n01).at(n01) += r;
        if (n02 != 0) Z_Matrix.at(n02).at(n02) += r;

        if(n01 != 0.0 && n02 != 0.0) {
            Z_Matrix.at(n01).at(n02) -= r;
            Z_Matrix.at(n02).at(n01) -= r;      
        };
    };

    // To verify the matrix
    for(int row = 1; row < nodesNum; row++) {
        for(int column = 1; column < nodesNum; column++) {
            std::cout << std::setw(20) << Z_Matrix.at(row).at(column);
        }
        std::cout << "\n";
    };

};
void Circuit::findNodeVolatge() {
    std::cout << "\n1st Gaussian Elimination belongs here\n";
};
void Circuit::findMeshCurrent() {
    std::cout << "\n2nd Gaussian Elimination belongs here\n";
};
void Circuit::printResult() {
    for(int l = 0; l < components.size(); l++) {
        components[l]->PrintOut();
    };
};