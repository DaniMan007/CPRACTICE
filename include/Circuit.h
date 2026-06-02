#pragma once
#include "Node.h"
#include "Component.h"
#include <vector>

class Circuit {
    private:
        std::vector<Node*> nodes;
        std::vector<Component*> components;
        std::vector<std::vector<float>> Y_Matrix;
        std::vector<std::vector<float>> Z_Matrix;

    public:
        // Constructor & Deconstructor
        Circuit();
        ~Circuit();

        // Construction of the circuit
        void addNode(Node* node);
        void addComponent(Component* component);

        // Calculations and the Workload
        void buildAdmittanceMatrix();
        void buildImpedanceMatrix();
        void findNodeVolatge();
        void findMeshCurrent();

        // Display of results
        void printResult();
};