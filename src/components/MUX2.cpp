#include "MUX2.h"
#include <stdexcept>

// Constructor
MUX2::MUX2(Node* input_a, Node* input_b, Node* select, Node* output):
    input_a(input_a),
    input_b(input_b),
    select(select),
    output(output),

    not_select(false),

    nand_a(false),
    and_a(false),

    nand_b(false),
    and_b(false),

    nor_output(false),

    select_inverter(select, &not_select),

    nand2_a(input_a, &not_select, &nand_a),
    inverter_a(&nand_a, &and_a),

    nand2_b(input_b, select, &nand_b),
    inverter_b(&nand_b, &and_b),

    nor2(&and_a, &and_b, &nor_output),
    output_inverter(&nor_output, output),

    counter(0){
}


// Getters
Node* MUX2::getInputA() const{
    return input_a;
}

Node* MUX2::getInputB() const{
    return input_b;
}

Node* MUX2::getSelect() const{
    return select;
}

Node* MUX2::getOutput() const{
    return output;
}


// Main update logic
void MUX2::update(){
    if(
        input_a == nullptr ||
        input_b == nullptr ||
        select == nullptr ||
        output == nullptr
    ){
        throw std::runtime_error("MUX2 inputs or output not connected!");
    }

    // Tick 1
    if(counter == 0){
        select_inverter.update();
        nand2_b.update();
    }

    // Tick 2
    else if(counter == 1){
        nand2_a.update();
        inverter_b.update();
    }

    // Tick 3
    else if(counter == 2){
        inverter_a.update();
    }

    // Tick 4
    else if(counter == 3){
        nor2.update();
    }

    // Tick 5
    else if(counter == 4){
        output_inverter.update();
    }

    counter = (counter + 1) % 5;
}


// Get current output value
bool MUX2::getOutputVal() const{
    if(output == nullptr){
        throw std::runtime_error("MUX2 output is null!");
    }

    return output->getSignal();
}