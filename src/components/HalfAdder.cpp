#include "HalfAdder.h"
#include <stdexcept>

// Constructor
HalfAdder::HalfAdder(Node* input_a, Node* input_b, Node* sum, Node* carry):
    input_a(input_a),
    input_b(input_b),
    sum(sum),
    carry(carry),
    carry_middle(false),
    nand2(input_a, input_b, &carry_middle),
    inverter(&carry_middle, carry),
    xor2(input_a, input_b, sum),
    counter(0){
}


// Getters
Node* HalfAdder::getInputA() const{
    return input_a;
}

Node* HalfAdder::getInputB() const{
    return input_b;
}

Node* HalfAdder::getSum() const{
    return sum;
}

Node* HalfAdder::getCarry() const{
    return carry;
}

//The main update logic
void HalfAdder::update(){
    if (input_a == nullptr || input_b == nullptr || sum == nullptr || carry == nullptr){
        throw std::runtime_error("Half Adder inputs or outputs not connected!");
    }

    //Simulating gate delay by propagating level by level in logic
    if(counter == 0){
        nand2.update();
        xor2.update();
    }
    else if(counter == 1){
        inverter.update();
    }
    
    counter = (counter + 1) % 2;
}


// Get current sum value
bool HalfAdder::getSumVal() const{
    if(sum == nullptr){
        throw std::runtime_error("HalfAdder sum is null!");
    }

    return sum->getSignal();
}


// Get current carry value
bool HalfAdder::getCarryVal() const{
    if(carry == nullptr){
        throw std::runtime_error("HalfAdder carry is null!");
    }

    return carry->getSignal();
}