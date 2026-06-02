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
    
    /*Creating a N x N matrix filled with zeros using vectors;
    This is the standard way of creating dynamic arrays, matrices.
    */
    std::vector<std::vector<float>> Y_Matrix(nodesNum, std::vector<float>(nodesNum, 0.0));

    // The Stamping Algorithm
    for(int k = 0; k < components.size(); k++) {
        Component* compName = components[k];

        // Getting the node ID's
        int n01 = compName->get01()->getId();
        int n02 = compName->get02()->getId();

        // Getting the conductacne
        float g = compName->getConductance();

        // This is the c++ version of the nodal analysis rule: Add conductances to the diagonal entries and subtract them from no-diagonal entries
        if(n01 != 0.0 && n02 != 0.0) {
            Y_Matrix[n01][n01] += g;
            Y_Matrix[n02][n02] += g;
        };
        if(n01 != 0.0 && n02 != 0.0) {
            Y_Matrix[n01][n02] -= g;
            Y_Matrix[n02][n01] -= g;      
        };
    };

    // To verify the matrix
    for(int row = 1; row < nodesNum; row++) {
        for(int column = 1; column < nodesNum; column++) {
            std::cout << std::setw(10) << Y_Matrix[row][column];
        }
        std::cout << ' \n';
    };
};

void Circuit::findNodeVolatge() {
    std::cout << "\n1st Gaussian Elimination belongs here\n";
};

void Circuit::findMeshCurrent() {
    std::cout << "\n2nd Gaussian Elimination belongs here\n";
};

void Circuit::printResult() {
    std::cout << "Just checking\n";
    for(int l = 0; l < components.size(); l++) {
        components[l]->PrintOut();
    };
};