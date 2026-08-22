#include "components/HalfAdder.h"
#include <cassert>

// 0 + 0 = Sum 0, Carry 0
void testHalfAdder00(){
    Node input_a(false);
    Node input_b(false);
    Node sum(true);
    Node carry(true);

    HalfAdder half_adder(&input_a, &input_b, &sum, &carry);

    half_adder.update();
    half_adder.update();

    assert(half_adder.getSumVal() == false);
    assert(half_adder.getCarryVal() == false);
}

// 0 + 1 = Sum 1, Carry 0
void testHalfAdder01(){
    Node input_a(false);
    Node input_b(true);
    Node sum(false);
    Node carry(true);

    HalfAdder half_adder(&input_a, &input_b, &sum, &carry);

    half_adder.update();
    half_adder.update();

    assert(half_adder.getSumVal() == true);
    assert(half_adder.getCarryVal() == false);
}

// 1 + 0 = Sum 1, Carry 0
void testHalfAdder10(){
    Node input_a(true);
    Node input_b(false);
    Node sum(false);
    Node carry(true);

    HalfAdder half_adder(&input_a, &input_b, &sum, &carry);

    half_adder.update();
    half_adder.update();

    assert(half_adder.getSumVal() == true);
    assert(half_adder.getCarryVal() == false);
}

// 1 + 1 = Sum 0, Carry 1
void testHalfAdder11(){
    Node input_a(true);
    Node input_b(true);
    Node sum(true);
    Node carry(false);

    HalfAdder half_adder(&input_a, &input_b, &sum, &carry);

    half_adder.update();
    half_adder.update();

    assert(half_adder.getSumVal() == false);
    assert(half_adder.getCarryVal() == true);
}

// Sum should propagate after one tick,
// while Carry should propagate after two ticks.
void testHalfAdderPropagation(){
    Node input_a(true);
    Node input_b(true);

    // Start opposite to the expected final values.
    Node sum(true);
    Node carry(false);

    HalfAdder half_adder(&input_a, &input_b, &sum, &carry);

    // Tick 1:
    // XOR and NAND update.
    half_adder.update();

    assert(sum.getSignal() == false);

    // Carry has not passed through the inverter yet.
    assert(carry.getSignal() == false);

    // Tick 2:
    // Inverter updates.
    half_adder.update();

    assert(carry.getSignal() == true);
}

// Inputs can change after a complete propagation cycle.
void testHalfAdderInputChanges(){
    Node input_a(false);
    Node input_b(false);
    Node sum(false);
    Node carry(false);

    HalfAdder half_adder(&input_a, &input_b, &sum, &carry);

    // 0 + 0
    half_adder.update();
    half_adder.update();

    assert(half_adder.getSumVal() == false);
    assert(half_adder.getCarryVal() == false);

    // 1 + 0
    input_a.setSignal(true);

    half_adder.update();
    half_adder.update();

    assert(half_adder.getSumVal() == true);
    assert(half_adder.getCarryVal() == false);

    // 1 + 1
    input_b.setSignal(true);

    half_adder.update();
    half_adder.update();

    assert(half_adder.getSumVal() == false);
    assert(half_adder.getCarryVal() == true);

    // 0 + 1
    input_a.setSignal(false);

    half_adder.update();
    half_adder.update();

    assert(half_adder.getSumVal() == true);
    assert(half_adder.getCarryVal() == false);
}

int main(){

    testHalfAdder00();
    testHalfAdder01();
    testHalfAdder10();
    testHalfAdder11();
    testHalfAdderPropagation();
    testHalfAdderInputChanges();

    return 0;
}