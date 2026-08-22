#include "ALU1.h"
#include <stdexcept>

// Constructor
ALU1::ALU1(
    Node* input_a,
    Node* input_b,
    Node* carry_in,
    Node* op0,
    Node* op1,
    Node* output,
    Node* carry_out
):
    input_a(input_a),
    input_b(input_b),
    carry_in(carry_in),
    op0(op0),
    op1(op1),
    output(output),
    carry_out(carry_out),

    nand_middle(false),
    and_output(false),

    nor2_middle(false),
    or_output(false),

    xor_output(false),

    full_adder_sum(false),

    mux_a_output(false),
    mux_b_output(false),

    nand(input_a, input_b, &nand_middle),
    inverter_nand(&nand_middle, &and_output),

    nor2(input_a, input_b, &nor2_middle),
    inverter_nor(&nor2_middle, &or_output),

    xor2(input_a, input_b, &xor_output),

    full_adder(input_a, input_b, carry_in, &full_adder_sum, carry_out),

    // op0 = 0: ADD / AND
    // op0 = 1: OR / XOR
    mux_a(&full_adder_sum, &or_output, op0, &mux_a_output),
    mux_b(&and_output, &xor_output, op0, &mux_b_output),

    // op1 chooses between the two remaining paths
    mux_output(&mux_a_output, &mux_b_output, op1, output),

    counter(0){
}


// Getters
Node* ALU1::getInputA() const{
    return input_a;
}

Node* ALU1::getInputB() const{
    return input_b;
}

Node* ALU1::getCarryIn() const{
    return carry_in;
}

Node* ALU1::getOp0() const{
    return op0;
}

Node* ALU1::getOp1() const{
    return op1;
}

Node* ALU1::getOutput() const{
    return output;
}

Node* ALU1::getCarryOut() const{
    return carry_out;
}


// Main update logic
void ALU1::update(){
    if(
        input_a == nullptr ||
        input_b == nullptr ||
        carry_in == nullptr ||
        op0 == nullptr ||
        op1 == nullptr ||
        output == nullptr ||
        carry_out == nullptr
    ){
        throw std::runtime_error("ALU1 inputs or outputs not connected!");
    }

    // Ticks 1-5: Calculate candidate operations
    if(counter < 5){

        // Full Adder requires all 5 ticks
        full_adder.update();

        // First logic layer
        if(counter == 0){
            nand.update();
            nor2.update();
            xor2.update();
        }

        // Second logic layer
        else if(counter == 1){
            inverter_nand.update();
            inverter_nor.update();
        }
    }

    // Ticks 6-10: First MUX layer
    else if(counter < 10){
        mux_a.update();
        mux_b.update();
    }

    // Ticks 11-15: Final MUX
    else{
        mux_output.update();
    }

    counter = (counter + 1) % 15;
}


// Get current output value
bool ALU1::getOutputVal() const{
    if(output == nullptr){
        throw std::runtime_error("ALU1 output is null!");
    }

    return output->getSignal();
}


// Get current carry out value
bool ALU1::getCarryOutVal() const{
    if(carry_out == nullptr){
        throw std::runtime_error("ALU1 carry out is null!");
    }

    return carry_out->getSignal();
}