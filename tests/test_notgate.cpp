#include "NotGate.h"
#include <cassert>

// Input LOW should produce output HIGH.
void testNotGateLowInput(){
    Node input(false);
    Node output(false);

    NotGate gate(&input, &output);

    gate.update();

    assert(gate.getOutputVal() == true);
    assert(output.getSignal() == true);
}

// Input HIGH should produce output LOW.
void testNotGateHighInput(){
    Node input(true);
    Node output(true);

    NotGate gate(&input, &output);

    gate.update();

    assert(gate.getOutputVal() == false);
    assert(output.getSignal() == false);
}

// Changing the input should cause the output to invert after update.
void testNotGateInputChange(){
    Node input(false);
    Node output(false);

    NotGate gate(&input, &output);

    gate.update();
    assert(gate.getOutputVal() == true);

    input.setSignal(true);
    gate.update();
    assert(gate.getOutputVal() == false);

    input.setSignal(false);
    gate.update();
    assert(gate.getOutputVal() == true);
}

// Test that changing the external input connection works.
void testSetInput(){
    Node input1(false);
    Node input2(true);
    Node output(false);

    NotGate gate(&input1, &output);

    gate.update();
    assert(gate.getOutputVal() == true);

    gate.setInput(&input2);
    gate.update();

    assert(gate.getOutputVal() == false);
}

// Test that changing the external output connection works.
void testSetOutput(){
    Node input(false);
    Node output1(false);
    Node output2(false);

    NotGate gate(&input, &output1);

    gate.update();
    assert(output1.getSignal() == true);

    gate.setOutput(&output2);
    gate.update();

    assert(output2.getSignal() == true);
}

int main(){

    testNotGateLowInput();
    testNotGateHighInput();
    testNotGateInputChange();
    testSetInput();
    testSetOutput();

    return 0;
}