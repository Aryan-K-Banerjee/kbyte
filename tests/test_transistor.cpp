#include "Transistor.h"
#include <cassert>

// NMOS should conduct when the gate is high.
void testNMOSOn(){
    Node source(true);
    Node gate(true);
    Node drain(false);

    Transistor transistor(
        Transistor::NMOS,
        &source,
        &gate,
        &drain
    );

    transistor.update();

    assert(drain.getSignal() == true);
    assert(transistor.getOutputVal() == true);
}

// NMOS should not conduct when the gate is low.
void testNMOSOff(){
    Node source(true);
    Node gate(false);
    Node drain(false);

    Transistor transistor(
        Transistor::NMOS,
        &source,
        &gate,
        &drain
    );

    transistor.update();

    // Drain remains unchanged because the transistor is off.
    assert(drain.getSignal() == false);
}

// PMOS should conduct when the gate is low.
void testPMOSOn(){
    Node source(true);
    Node gate(false);
    Node drain(false);

    Transistor transistor(
        Transistor::PMOS,
        &source,
        &gate,
        &drain
    );

    transistor.update();

    assert(drain.getSignal() == true);
    assert(transistor.getOutputVal() == true);
}

// PMOS should not conduct when the gate is high.
void testPMOSOff(){
    Node source(true);
    Node gate(true);
    Node drain(false);

    Transistor transistor(
        Transistor::PMOS,
        &source,
        &gate,
        &drain
    );

    transistor.update();

    // Drain remains unchanged because the transistor is off.
    assert(drain.getSignal() == false);
}

int main(){

    testNMOSOn();
    testNMOSOff();
    testPMOSOn();
    testPMOSOff();

    return 0;
}