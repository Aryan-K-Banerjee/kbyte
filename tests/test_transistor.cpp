#include "Transistor.h"
#include <cassert>
#include <stdexcept>

// NMOS should conduct when the gate is high.
void testNMOSOn(){
    Node source(true);
    Node drain(false);
    Node gate(true);

    Transistor transistor(Transistor::NMOS, &drain, &source, &gate);

    transistor.update();

    assert(transistor.getOutput() == true);
}

// NMOS should not conduct when the gate is low.
void testNMOSOff(){
    Node source(true);
    Node drain(false);
    Node gate(false);

    Transistor transistor(Transistor::NMOS, &drain, &source, &gate);

    transistor.update();

    // Drain should remain unchanged.
    assert(transistor.getOutput() == false);
}

// PMOS should conduct when the gate is low.
void testPMOSOn(){
    Node source(true);
    Node drain(false);
    Node gate(false);

    Transistor transistor(Transistor::PMOS, &drain, &source, &gate);

    transistor.update();

    assert(transistor.getOutput() == true);
}

// PMOS should not conduct when the gate is high.
void testPMOSOff(){
    Node source(true);
    Node drain(false);
    Node gate(true);

    Transistor transistor(Transistor::PMOS, &drain, &source, &gate);

    transistor.update();

    // Drain should remain unchanged.
    assert(transistor.getOutput() == false);
}

// Updating an unconnected transistor should throw an error.
void testUnconnectedTransistor(){
    Transistor transistor;

    bool threwError = false;

    try{
        transistor.update();
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
    testUnconnectedTransistor();

    return 0;
}