#pragma once
#include "Component.h"

class Resistor: public Component{
    public:
        // The constructor gives all its parameters 
        Resistor(std::string compName, Node* n01, Node* n02, float resistance);   
        
        // Override to ensure the function gets written correctly and no mispells
        float getConductance() const override;
        void PrintOut() const override;
};