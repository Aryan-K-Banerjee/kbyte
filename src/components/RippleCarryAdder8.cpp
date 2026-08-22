#include "RippleCarryAdder8.h"
#include <stdexcept>

// Constructor
RippleCarryAdder8::RippleCarryAdder8(
    std::array<Node*, 8> input_a,
    std::array<Node*, 8> input_b,
    Node* carry_in,
    std::array<Node*, 8> sum,
    Node* carry_out
):
    input_a(input_a),
    input_b(input_b),
    sum(sum),

    carry_in(carry_in),
    carry_out(carry_out),

    carry_0(false),
    carry_1(false),
    carry_2(false),
    carry_3(false),
    carry_4(false),
    carry_5(false),
    carry_6(false),

    bit_0(input_a[0], input_b[0], carry_in, sum[0], &carry_0),
    bit_1(input_a[1], input_b[1], &carry_0, sum[1], &carry_1),
    bit_2(input_a[2], input_b[2], &carry_1, sum[2], &carry_2),
    bit_3(input_a[3], input_b[3], &carry_2, sum[3], &carry_3),
    bit_4(input_a[4], input_b[4], &carry_3, sum[4], &carry_4),
    bit_5(input_a[5], input_b[5], &carry_4, sum[5], &carry_5),
    bit_6(input_a[6], input_b[6], &carry_5, sum[6], &carry_6),
    bit_7(input_a[7], input_b[7], &carry_6, sum[7], carry_out),

    full_adders{
        &bit_0,
        &bit_1,
        &bit_2,
        &bit_3,
        &bit_4,
        &bit_5,
        &bit_6,
        &bit_7
    },

    counter(0){
}


// Main update logic
void RippleCarryAdder8::update(){
    if(carry_in == nullptr || carry_out == nullptr){
        throw std::runtime_error("Ripple Carry Adder carry is not connected!");
    }

    // Each Full Adder gets 5 propagation ticks.
    int current_bit = counter / 5;

    full_adders[current_bit]->update();

    counter = (counter + 1) % 40;
}


// Get one sum bit
bool RippleCarryAdder8::getSumVal(int bit) const{
    if(bit < 0 || bit >= 8){
        throw std::runtime_error("Ripple Carry Adder bit index is invalid!");
    }

    return sum[bit]->getSignal();
}


// Get final carry out
bool RippleCarryAdder8::getCarryOutVal() const{
    if(carry_out == nullptr){
        throw std::runtime_error("Ripple Carry Adder carry out is null!");
    }

    return carry_out->getSignal();
}