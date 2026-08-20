#include "gates/NOR2.h"
#include <cassert>

// 0 NOR 0 = 1
void testNOR00(){
    Node input_a(false);
    Node input_b(false);
    Node output(false);

    NOR2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == true);
    assert(output.getSignal() == true);
}

// 0 NOR 1 = 0
void testNOR01(){
    Node input_a(false);
    Node input_b(true);
    Node output(true);

    NOR2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == false);
    assert(output.getSignal() == false);
}

// 1 NOR 0 = 0
void testNOR10(){
    Node input_a(true);
    Node input_b(false);
    Node output(true);

    NOR2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == false);
    assert(output.getSignal() == false);
}

// 1 NOR 1 = 0
void testNOR11(){
    Node input_a(true);
    Node input_b(true);
    Node output(true);

    NOR2 gate(&input_a, &input_b, &output);

    gate.update();

    assert(gate.getOutputVal() == false);
    assert(output.getSignal() == false);
}

// Changing inputs should update NOR correctly.
void testNORInputChanges(){
    Node input_a(false);
    Node input_b(false);
    Node output(false);

    NOR2 gate(&input_a, &input_b, &output);

    gate.update();
    assert(gate.getOutputVal() == true);

    input_a.setSignal(true);
    gate.update();
    assert(gate.getOutputVal() == false);

    input_b.setSignal(true);
    gate.update();
    assert(gate.getOutputVal() == false);

    input_a.setSignal(false);
    gate.update();
    assert(gate.getOutputVal() == false);

    input_b.setSignal(false);
    gate.update();
    assert(gate.getOutputVal() == true);
}

int main(){

    testNOR00();
    testNOR01();
    testNOR10();
    testNOR11();
    testNORInputChanges();

    return 0;
}