#include "NAND2.h"
#include <stdexcept>

//constructor
NAND2::NAND2(Node* input_a, Node* input_b, Node* output):
    vdd(true),
    ground(false),
    middle(false),
    input_a(input_a),
    input_b(input_b),
    output(output),
    pmos_a(Transistor::PMOS, &vdd, input_a, output),
    pmos_b(Transistor::PMOS, &vdd, input_b, output),
    nmos_a(Transistor::NMOS, &middle, input_a, output),
    nmos_b(Transistor::NMOS, &ground, input_b, &middle),
    circuit(
        {&vdd, &ground, &middle, input_a, input_b, output},
        {&vdd, &ground, input_a, input_b},
        {&pmos_a, &pmos_b, &nmos_a, &nmos_b}
    ){
}


// Getters
Node* NAND2::getInputA() const{
    return input_a;
}

Node* NAND2::getInputB() const{
    return input_b;
}

Node* NAND2::getOutput() const{
    return output;
}


// Update NAND gate state
void NAND2::update(){
    if(input_a == nullptr || input_b == nullptr || output == nullptr){
        throw std::runtime_error("NAND2 inputs or output are not connected!");
    }
    circuit.evaluate();
}


// Get current output value
bool NAND2::getOutputVal() const{
    if(output == nullptr){
        throw std::runtime_error("NAND2 output is null!");
    }

    return output->getSignal();
}