#include "Transistor.h"
#include <stdexcept>

// Constructor
Transistor::Transistor(Transistor_Type type, Node* source, Node* gate, Node* drain) :
    type(type),
    source(source),
    gate(gate),
    drain(drain) {
}

//Setters
void Transistor::setType(Transistor_Type type){
    this->type = type;
}

void Transistor::connectSource(Node* source){
    this->source = source;
}

void Transistor::connectGate(Node* gate){
    this->gate = gate;
}

void Transistor::connectDrain(Node* drain){
    this->drain = drain;
}

//Getters
Transistor::Transistor_Type Transistor::getType() const{
    return type;
}

Node* Transistor::getSource() const{
    return source;
}

Node* Transistor::getGate() const{
    return gate;
}

Node* Transistor::getDrain() const{
    return drain;
}

//Main function to update the logic and run the transistor
void Transistor::update() {
    if(drain == nullptr || source == nullptr || gate == nullptr){
        throw std::runtime_error("Transistor has an unconnected node!");
    }

    if(type == NMOS){
        if(gate->getSignal()){
            drain->setSignal(source->getSignal());
        }
    }
    else if(type == PMOS){
        if(!gate->getSignal()){
            drain->setSignal(source->getSignal());
        }
    }
    else{
        throw std::runtime_error("Transistor has an invalid type!");
    }
}

bool Transistor::getOutputVal() const{
    if(drain == nullptr){
        throw std::runtime_error("Drain is Null, cannot get Output!");
    }
    return drain->getSignal();
}