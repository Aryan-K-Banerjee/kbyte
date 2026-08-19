//src/circuits/Node.cpp
#include "Node.h"

// Constructor
Node::Node(bool initialValue) : 
    signal(initialValue){
}

// Methods
void Node::setSignal(bool value){
    signal = value;
}

bool Node::getSignal() const {
    return signal;
}