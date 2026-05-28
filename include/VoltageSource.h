#pragma once
#include "Component.h"

class VoltageSource: public Component {
    public:
        // Constructor
        VoltageSource(std::string compName, Node* n01, Node* n02, float voltage);

        // Override to ensure the function gets written correctly and no mispells
        // Note: Ideal volatage sources have infinite conductance
        float getConductance() const override;
        void PrintOut() const override;
};