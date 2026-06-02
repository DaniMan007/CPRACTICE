#include "Component.h"
#include "iostream"

// The constructor for initializing the protected variables
Component::Component(std::string compName, Node* n01, Node* n02, float value):
    Name(compName), node01(n01), node02(n02), value(value) {};

// Handles the getters
std::string Component::getName() const {
    return Name;
};
Node* Component::get01() const {
    return node01;
};
Node* Component::get02() const {
    return node02;
};
float Component::getValue() const {
    return value;
};

// The print function
/*Note: To call a function from a pointer, there a two ways for that;
        (i) using the arrow operator {'variable -> function'}
        (ii) using the ancient dereferencing method{'(*variable).function'}
*/ 
void Component::PrintOut() const {
    std::cout << Name << '\n';
    std::cout << "Connected across nodes: " << node01->getId() << " and " << (*node02).getId();
};