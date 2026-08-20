#include "XOR2.h"
#include <stdexcept>

// Constructor
XOR2::XOR2(Node* input_a, Node* input_b, Node* output):
    vdd(true),
    ground(false),

    not_a(false),
    xnor(false),

    input_a(input_a),
    input_b(input_b),
    output(output),

    // Invert A
    inv_a_pmos(Transistor::PMOS, &vdd, input_a, &not_a),
    inv_a_nmos(Transistor::NMOS, &ground, input_a, &not_a),

    // B = 0 -> pass NOT A
    pass_not_a(Transistor::PMOS, &not_a, input_b, &xnor),

    // B = 1 -> pass A
    pass_a(Transistor::NMOS, input_a, input_b, &xnor),

    // Invert XNOR to produce XOR
    out_pmos(Transistor::PMOS, &vdd, &xnor, output),
    out_nmos(Transistor::NMOS, &ground, &xnor, output),

    circuit(
        {
            &vdd,
            &ground,
            &not_a,
            &xnor,
            input_a,
            input_b,
            output
        },
        {
            &vdd,
            &ground,
            input_a,
            input_b
        },
        {
            &inv_a_pmos,
            &inv_a_nmos,
            &pass_not_a,
            &pass_a,
            &out_pmos,
            &out_nmos
        }
    ){
}

Node* XOR2::getInputA() const{
    return input_a;
}

Node* XOR2::getInputB() const{
    return input_b;
}

Node* XOR2::getOutput() const{
    return output;
}

void XOR2::update(){
    if(input_a == nullptr || input_b == nullptr || output == nullptr){
        throw std::runtime_error("XOR2 inputs or output are not connected!");
    }

    circuit.evaluate();
}

bool XOR2::getOutputVal() const{
    if(output == nullptr){
        throw std::runtime_error("XOR2 output is null!");
    }

    return output->getSignal();
}