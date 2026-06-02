#pragma once
#include "Node.h"

class Component {
    // 'protected' variables in classes just simply mean that the child classes can modify them but are 'protected' from the outside world
    protected:
        // '::' is a scope resolution operator which tells the compiler that the function on the right belongs to the class on the left
        // The variables; 'node01' & 'node02' are merely just addresses while the '*' are pointers
        std::string Name;
        Node* node01;
        Node* node02;
        float value;

    public:
        // Constructor
        Component(std::string compName, Node* n01, Node* n02, float value);

        // Virtual destructor to prevent memory leaks
        // The 'virtual' keyword ensures that the compiler treats everything with uniformity
        virtual ~Component() = default;

        // Getters
        // The 'const' variable is written at the end of each function to ensure that the functions only read data and don't modify the object
        std::string getName() const;
        Node* get01() const;
        Node* get02() const;
        float getValue() const;
        virtual float getConductance() const = 0;

        // Prints component details onto the console
        virtual void PrintOut() const;
};