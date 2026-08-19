#include "Inverter.h"
#include <stdexcept>

// Constructor
Inverter::Inverter(Node* input, Node* output):
    vdd(true),
    ground(false),
    input(input),
    output(output),
    pmos(Transistor::PMOS, &vdd, input, output),
    nmos(Transistor::NMOS, &ground, input, output),
    circuit(
        {&vdd, &ground, input, output},
        {&vdd, &ground, input},
        {&pmos, &nmos}){
}

//Getters
Node* Inverter::getInput() const{
    return input;
}

Node* Inverter::getOutput() const{
    return output;
}

//The main update function to calculate logic
void Inverter::update(){
    if(input == nullptr || output == nullptr){
        throw std::runtime_error("Inverter has an unconnected Node!");
    }

    circuit.evaluate();
}

//Get current output value
bool Inverter::getOutputVal() const{
    if(output == nullptr){
        throw std::runtime_error("Inverter Output is Null!");
    }
    return output->getSignal();
}