#include "gates/XOR2.h"
#include <cassert>

// 0 XOR 0 = 0
void testXOR00(){
    Node input_a(false);
    Node input_b(false);
    Node output(true);

    XOR2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == false);
    assert(output.getSignal() == false);
}

// 0 XOR 1 = 1
void testXOR01(){
    Node input_a(false);
    Node input_b(true);
    Node output(false);

    XOR2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == true);
    assert(output.getSignal() == true);
}

// 1 XOR 0 = 1
void testXOR10(){
    Node input_a(true);
    Node input_b(false);
    Node output(false);

    XOR2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == true);
    assert(output.getSignal() == true);
}

// 1 XOR 1 = 0
void testXOR11(){
    Node input_a(true);
    Node input_b(true);
    Node output(true);

    XOR2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == false);
    assert(output.getSignal() == false);
}

// Changing inputs should update XOR correctly.
void testXORInputChanges(){
    Node input_a(false);
    Node input_b(false);
    Node output(false);

    XOR2 gate(&input_a, &input_b, &output);

    gate.update();
    assert(gate.getOutputVal() == false);

    input_b.setSignal(true);
    gate.update();
    assert(gate.getOutputVal() == true);

    input_a.setSignal(true);
    gate.update();
    assert(gate.getOutputVal() == false);

    input_b.setSignal(false);
    gate.update();
    assert(gate.getOutputVal() == true);

    input_a.setSignal(false);
    gate.update();
    assert(gate.getOutputVal() == false);
}

int main(){

    testXOR00();
    testXOR01();
    testXOR10();
    testXOR11();
    testXORInputChanges();

    return 0;
}