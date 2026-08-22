#include "cpu/ALU1.h"
#include <cassert>


// Fully propagate through the ALU.
void settle(ALU1& alu){
    for(int i = 0; i < 15; i++){
        alu.update();
    }
}


// 1 + 0 + 0 = 1
void testADD(){
    Node a(true);
    Node b(false);
    Node carry_in(false);

    Node op0(false);
    Node op1(false);

    Node output(false);
    Node carry_out(false);

    ALU1 alu(
        &a,
        &b,
        &carry_in,
        &op0,
        &op1,
        &output,
        &carry_out
    );

    settle(alu);

    assert(alu.getOutputVal() == true);
    assert(alu.getCarryOutVal() == false);
}


// 1 + 1 + 0 = 0, Carry = 1
void testADDCarry(){
    Node a(true);
    Node b(true);
    Node carry_in(false);

    Node op0(false);
    Node op1(false);

    Node output(true);
    Node carry_out(false);

    ALU1 alu(
        &a,
        &b,
        &carry_in,
        &op0,
        &op1,
        &output,
        &carry_out
    );

    settle(alu);

    assert(alu.getOutputVal() == false);
    assert(alu.getCarryOutVal() == true);
}


// 1 AND 0 = 0
void testAND(){
    Node a(true);
    Node b(false);
    Node carry_in(false);

    Node op0(false);
    Node op1(true);

    Node output(true);
    Node carry_out(false);

    ALU1 alu(
        &a,
        &b,
        &carry_in,
        &op0,
        &op1,
        &output,
        &carry_out
    );

    settle(alu);

    assert(alu.getOutputVal() == false);
}


// 1 AND 1 = 1
void testANDTrue(){
    Node a(true);
    Node b(true);
    Node carry_in(false);

    Node op0(false);
    Node op1(true);

    Node output(false);
    Node carry_out(false);

    ALU1 alu(
        &a,
        &b,
        &carry_in,
        &op0,
        &op1,
        &output,
        &carry_out
    );

    settle(alu);

    assert(alu.getOutputVal() == true);
}


// 0 OR 1 = 1
void testOR(){
    Node a(false);
    Node b(true);
    Node carry_in(false);

    Node op0(true);
    Node op1(false);

    Node output(false);
    Node carry_out(false);

    ALU1 alu(
        &a,
        &b,
        &carry_in,
        &op0,
        &op1,
        &output,
        &carry_out
    );

    settle(alu);

    assert(alu.getOutputVal() == true);
}


// 1 XOR 1 = 0
void testXORFalse(){
    Node a(true);
    Node b(true);
    Node carry_in(false);

    Node op0(true);
    Node op1(true);

    Node output(true);
    Node carry_out(false);

    ALU1 alu(
        &a,
        &b,
        &carry_in,
        &op0,
        &op1,
        &output,
        &carry_out
    );

    settle(alu);

    assert(alu.getOutputVal() == false);
}


// 1 XOR 0 = 1
void testXORTrue(){
    Node a(true);
    Node b(false);
    Node carry_in(false);

    Node op0(true);
    Node op1(true);

    Node output(false);
    Node carry_out(false);

    ALU1 alu(
        &a,
        &b,
        &carry_in,
        &op0,
        &op1,
        &output,
        &carry_out
    );

    settle(alu);

    assert(alu.getOutputVal() == true);
}


// Changing opcode should select a different result.
void testOperationChange(){
    Node a(true);
    Node b(false);
    Node carry_in(false);

    Node op0(false);
    Node op1(false);

    Node output(false);
    Node carry_out(false);

    ALU1 alu(
        &a,
        &b,
        &carry_in,
        &op0,
        &op1,
        &output,
        &carry_out
    );

    // ADD: 1 + 0 = 1
    settle(alu);
    assert(alu.getOutputVal() == true);

    // AND: 1 AND 0 = 0
    op1.setSignal(true);

    settle(alu);
    assert(alu.getOutputVal() == false);

    // XOR: 1 XOR 0 = 1
    op0.setSignal(true);

    settle(alu);
    assert(alu.getOutputVal() == true);

    // OR: 1 OR 0 = 1
    op1.setSignal(false);

    settle(alu);
    assert(alu.getOutputVal() == true);
}


int main(){

    testADD();
    testADDCarry();

    testAND();
    testANDTrue();

    testOR();

    testXORFalse();
    testXORTrue();

    testOperationChange();

    return 0;
}