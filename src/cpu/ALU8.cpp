#include "ALU8.h"
#include <stdexcept>

// Constructor
ALU8::ALU8(
    std::array<Node*, 8> input_a,
    std::array<Node*, 8> input_b,
    Node* carry_in,
    Node* op0,
    Node* op1,
    std::array<Node*, 8> output,
    Node* carry_out
):
    input_a(input_a),
    input_b(input_b),
    output(output),

    carry_in(carry_in),
    carry_out(carry_out),

    op0(op0),
    op1(op1),

    carry_0(false),
    carry_1(false),
    carry_2(false),
    carry_3(false),
    carry_4(false),
    carry_5(false),
    carry_6(false),

    alu_0(
        input_a[0],
        input_b[0],
        carry_in,
        op0,
        op1,
        output[0],
        &carry_0
    ),

    alu_1(
        input_a[1],
        input_b[1],
        &carry_0,
        op0,
        op1,
        output[1],
        &carry_1
    ),

    alu_2(
        input_a[2],
        input_b[2],
        &carry_1,
        op0,
        op1,
        output[2],
        &carry_2
    ),

    alu_3(
        input_a[3],
        input_b[3],
        &carry_2,
        op0,
        op1,
        output[3],
        &carry_3
    ),

    alu_4(
        input_a[4],
        input_b[4],
        &carry_3,
        op0,
        op1,
        output[4],
        &carry_4
    ),

    alu_5(
        input_a[5],
        input_b[5],
        &carry_4,
        op0,
        op1,
        output[5],
        &carry_5
    ),

    alu_6(
        input_a[6],
        input_b[6],
        &carry_5,
        op0,
        op1,
        output[6],
        &carry_6
    ),

    alu_7(
        input_a[7],
        input_b[7],
        &carry_6,
        op0,
        op1,
        output[7],
        carry_out
    ),

    alus{
        &alu_0,
        &alu_1,
        &alu_2,
        &alu_3,
        &alu_4,
        &alu_5,
        &alu_6,
        &alu_7
    },

    counter(0){
}


// Main update logic
void ALU8::update(){
    if(
        carry_in == nullptr ||
        carry_out == nullptr ||
        op0 == nullptr ||
        op1 == nullptr
    ){
        throw std::runtime_error("ALU8 inputs or outputs not connected!");
    }

    // Each ALU1 gets 15 ticks before moving to the next bit.
    int current_bit = counter / 15;

    alus[current_bit]->update();

    counter = (counter + 1) % 120;
}


// Get one output bit
bool ALU8::getOutputVal(int bit) const{
    if(bit < 0 || bit >= 8){
        throw std::runtime_error("ALU8 bit index is invalid!");
    }

    return output[bit]->getSignal();
}


// Get final carry out
bool ALU8::getCarryOutVal() const{
    if(carry_out == nullptr){
        throw std::runtime_error("ALU8 carry out is null!");
    }

    return carry_out->getSignal();
}