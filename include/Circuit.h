#pragma once
#include "Node.h"
#include "Component.h"
#include <vector>

class Circuit {
    private:
        std::vector<Node*> nodes;
        std::vector<Component*> components;

    public:
        // Constructor & Deconstructor
        Circuit();
        ~Circuit();

        // Construction of the circuit
        void addNode(Node* node);
        void addComponent(Component* component);

        // Calculations and the Workload
        void findNodeVolatge();
        void buildAdmittanceMatrix();
        void findMeshCurrent();

        // Display of results
        void printResult();
};