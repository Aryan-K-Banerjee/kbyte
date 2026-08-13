#include "Transistor.h"
#include <stdexcept>

// Constructors
Transistor::Transistor(): type(NMOS), drain(nullptr), source(nullptr), gate(nullptr) {    
}

Transistor::Transistor(Transistor_Type type, Node* drain, Node* source, Node* gate) :
                        type(type), drain(drain), source(source), gate(gate) {

}

//Setters
void Transistor::setType(Transistor_Type type){
    this->type = type;
}

void Transistor::connectDrain(Node* drain){
    this->drain = drain;
}

void Transistor::connectSource(Node* source){
    this->source = source;
}

void Transistor::connectGate(Node* gate){
    this->gate = gate;
}

//Getters
Transistor::Transistor_Type Transistor::getType() const{
    return type;
}

Node* Transistor::getDrain() const{
    return drain;
}

Node* Transistor::getSource() const{
    return source;
}

Node* Transistor::getGate() const{
    return gate;
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

bool Transistor::getOutput() const{
    if(drain == nullptr){
        throw std::runtime_error("Drain is Null, cannot get Output!");
    }
    return drain->getSignal();
}