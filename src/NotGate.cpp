#include "NotGate.h"
#include <stdexcept>

NotGate::NotGate(Node* input, Node* output):
    vdd(true),
    ground(false),
    input(input),
    output(output),
    pmos(Transistor::PMOS, &vdd, input, output),
    nmos(Transistor::NMOS, &ground, input, output){
}

void NotGate::setInput(Node* input){
    this->input = input;
    pmos.connectGate(input);
    nmos.connectGate(input);
}

void NotGate::setOutput(Node* output){
    this->output = output;
    pmos.connectDrain(output);
    nmos.connectDrain(output);
}

Node* NotGate::getInput() const{
    return this->input;
}

Node* NotGate::getOutput() const{
    return this->output;
}

void NotGate::update(){
    if(input == nullptr || output == nullptr){
        throw std::runtime_error("Not gate has an unconnected Node!");
    }
    pmos.update();
    nmos.update();
}

bool NotGate::getOutputVal() const{
    if(output == nullptr){
        throw std::runtime_error("Not Gate Output is Null!");
    }
    return output->getSignal();
}