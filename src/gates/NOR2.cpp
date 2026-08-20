#include "NOR2.h"
#include <stdexcept>

// Constructor
NOR2::NOR2(Node* input_a, Node* input_b, Node* output):
    vdd(true),
    ground(false),
    middle(false),
    input_a(input_a),
    input_b(input_b),
    output(output),

    // PMOS transistors in series
    pmos_a(Transistor::PMOS, &vdd, input_a, &middle),
    pmos_b(Transistor::PMOS, &middle, input_b, output),

    // NMOS transistors in parallel
    nmos_a(Transistor::NMOS, &ground, input_a, output),
    nmos_b(Transistor::NMOS, &ground, input_b, output),

    circuit(
        {&vdd, &ground, &middle, input_a, input_b, output},
        {&vdd, &ground, input_a, input_b},
        {&pmos_a, &pmos_b, &nmos_a, &nmos_b}
    ){
}

// Getters
Node* NOR2::getInputA() const{
    return input_a;
}

Node* NOR2::getInputB() const{
    return input_b;
}

Node* NOR2::getOutput() const{
    return output;
}

// Update NOR gate state
void NOR2::update(){
    if(input_a == nullptr || input_b == nullptr || output == nullptr){
        throw std::runtime_error("NOR2 inputs or output are not connected!");
    }

    circuit.evaluate();
}

// Get current output value
bool NOR2::getOutputVal() const{
    if(output == nullptr){
        throw std::runtime_error("NOR2 output is null!");
    }

    return output->getSignal();
}