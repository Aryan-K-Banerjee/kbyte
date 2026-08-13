#include "Node.h"

Node::Node() : signal(false) {
}

Node::Node(bool initialValue) : signal(initialValue){
}

void Node::setSignal(bool value){
    signal = value;
}

bool Node::getSignal() const {
    return signal;
}