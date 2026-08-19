#include "circuits/Transistor.h"
#include <cassert>
#include <stdexcept>

// NMOS should conduct when the gate is high.
void testNMOSOn(){
    Node source(false);
    Node gate(true);
    Node drain(false);

    Transistor transistor(
        Transistor::NMOS,
        &source,
        &gate,
        &drain
    );

    assert(transistor.isConducting() == true);
}

// NMOS should not conduct when the gate is low.
void testNMOSOff(){
    Node source(false);
    Node gate(false);
    Node drain(false);

    Transistor transistor(
        Transistor::NMOS,
        &source,
        &gate,
        &drain
    );

    assert(transistor.isConducting() == false);
}

// PMOS should conduct when the gate is low.
void testPMOSOn(){
    Node source(false);
    Node gate(false);
    Node drain(false);

    Transistor transistor(
        Transistor::PMOS,
        &source,
        &gate,
        &drain
    );

    assert(transistor.isConducting() == true);
}

// PMOS should not conduct when the gate is high.
void testPMOSOff(){
    Node source(false);
    Node gate(true);
    Node drain(false);

    Transistor transistor(
        Transistor::PMOS,
        &source,
        &gate,
        &drain
    );

    assert(transistor.isConducting() == false);
}

// Changing the gate should change the conduction state.
void testGateChange(){
    Node source(false);
    Node gate(false);
    Node drain(false);

    Transistor transistor(
        Transistor::NMOS,
        &source,
        &gate,
        &drain
    );

    assert(transistor.isConducting() == false);

    gate.setSignal(true);

    assert(transistor.isConducting() == true);
}

// An unconnected transistor should throw an error.
void testUnconnectedTransistor(){
    Node source(false);
    Node gate(true);

    Transistor transistor(
        Transistor::NMOS,
        &source,
        &gate,
        nullptr
    );

    bool threwError = false;

    try{
        transistor.isConducting();
    }
    catch(const std::runtime_error&){
        threwError = true;
    }

    assert(threwError == true);
}

int main(){

    testNMOSOn();
    testNMOSOff();
    testPMOSOn();
    testPMOSOff();
    testGateChange();
    testUnconnectedTransistor();

    return 0;
}