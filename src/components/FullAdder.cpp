#include "FullAdder.h"
#include <stdexcept>

// Constructor
FullAdder::FullAdder(
    Node* input_a,
    Node* input_b,
    Node* carry_in,
    Node* sum,
    Node* carry_out
):
    input_a(input_a),
    input_b(input_b),
    carry_in(carry_in),
    sum(sum),
    carry_out(carry_out),

    partial_sum(false),
    carry_1(false),
    carry_2(false),
    carry_middle(false),

    half_adder_1(input_a, input_b, &partial_sum, &carry_1),
    half_adder_2(&partial_sum, carry_in, sum, &carry_2),

    nor2(&carry_1, &carry_2, &carry_middle),
    inverter(&carry_middle, carry_out),

    counter(0){
}


// Getters
Node* FullAdder::getInputA() const{
    return input_a;
}

Node* FullAdder::getInputB() const{
    return input_b;
}

Node* FullAdder::getCarryIn() const{
    return carry_in;
}

Node* FullAdder::getSum() const{
    return sum;
}

Node* FullAdder::getCarryOut() const{
    return carry_out;
}


// Main update logic
void FullAdder::update(){
    if(
        input_a == nullptr ||
        input_b == nullptr ||
        carry_in == nullptr ||
        sum == nullptr ||
        carry_out == nullptr
    ){
        throw std::runtime_error("Full Adder inputs or outputs not connected!");
    }

    // Propagate one logic level per tick
    if(counter == 0){
        half_adder_1.update();
    }
    else if(counter == 1){
        half_adder_1.update();
        half_adder_2.update();
    }
    else if(counter == 2){
        half_adder_2.update();
    }
    else if(counter == 3){
        nor2.update();
    }
    else if(counter == 4){
        inverter.update();
    }

    counter = (counter + 1) % 5;
}


// Get current sum value
bool FullAdder::getSumVal() const{
    if(sum == nullptr){
        throw std::runtime_error("FullAdder sum is null!");
    }

    return sum->getSignal();
}


// Get current carry-out value
bool FullAdder::getCarryOutVal() const{
    if(carry_out == nullptr){
        throw std::runtime_error("FullAdder carry out is null!");
    }

    return carry_out->getSignal();
}