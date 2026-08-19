#include "gates/Inverter.h"
#include <cassert>

// Input LOW should produce output HIGH.
void testInverterLowInput(){
    Node input(false);
    Node output(false);

    Inverter inverter(&input, &output);

    inverter.update();

    assert(inverter.getOutputVal() == true);
    assert(output.getSignal() == true);
}

// Input HIGH should produce output LOW.
void testInverterHighInput(){
    Node input(true);
    Node output(true);

    Inverter inverter(&input, &output);

    inverter.update();

    assert(inverter.getOutputVal() == false);
    assert(output.getSignal() == false);
}

// Changing the input value should update the inverted output.
void testInverterInputChange(){
    Node input(false);
    Node output(false);

    Inverter inverter(&input, &output);

    inverter.update();
    assert(inverter.getOutputVal() == true);

    input.setSignal(true);
    inverter.update();
    assert(inverter.getOutputVal() == false);

    input.setSignal(false);
    inverter.update();
    assert(inverter.getOutputVal() == true);
}

int main(){

    testInverterLowInput();
    testInverterHighInput();
    testInverterInputChange();

    return 0;
}