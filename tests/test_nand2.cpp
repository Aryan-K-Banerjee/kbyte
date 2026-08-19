#include "gates/NAND2.h"
#include <cassert>

// 0 NAND 0 = 1
void testNAND00(){
    Node input_a(false);
    Node input_b(false);
    Node output(false);

    NAND2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == true);
    assert(output.getSignal() == true);
}

// 0 NAND 1 = 1
void testNAND01(){
    Node input_a(false);
    Node input_b(true);
    Node output(false);

    NAND2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == true);
    assert(output.getSignal() == true);
}

// 1 NAND 0 = 1
void testNAND10(){
    Node input_a(true);
    Node input_b(false);
    Node output(false);

    NAND2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == true);
    assert(output.getSignal() == true);
}

// 1 NAND 1 = 0
void testNAND11(){
    Node input_a(true);
    Node input_b(true);
    Node output(true);

    NAND2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == false);
    assert(output.getSignal() == false);
}

// Changing input values should update the NAND output correctly.
void testNANDInputChanges(){
    Node input_a(false);
    Node input_b(false);
    Node output(false);

    NAND2 gate(&input_a, &input_b, &output);

    gate.update();
    assert(gate.getOutputVal() == true);

    input_a.setSignal(true);
    gate.update();
    assert(gate.getOutputVal() == true);

    input_b.setSignal(true);
    gate.update();
    assert(gate.getOutputVal() == false);

    input_a.setSignal(false);
    gate.update();
    assert(gate.getOutputVal() == true);
}

int main(){

    testNAND00();
    testNAND01();
    testNAND10();
    testNAND11();
    testNANDInputChanges();

    return 0;
}