#pragma once
#include "Component.h"

class CurrentSource: public Component {
    public:
        // Constructor
        CurrentSource(std::string compName, Node* n01, Node* n02, float current);

        // Override to ensure the function gets written correctly and no mispells
        // Note: Ideal current sources have infinite resistance, thus zero conductance
        float getCurrent() const;
        float getConductance() const override;
        float getResistance() const override;
        void PrintOut() const override;
};