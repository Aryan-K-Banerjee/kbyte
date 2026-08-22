#include "cpu/ALU8.h"

#include <array>
#include <cassert>


std::array<Node*, 8> getPointers(std::array<Node, 8>& nodes){
    return {
        &nodes[0],
        &nodes[1],
        &nodes[2],
        &nodes[3],
        &nodes[4],
        &nodes[5],
        &nodes[6],
        &nodes[7]
    };
}


// Fully propagate through all 8 ALU slices.
void settle(ALU8& alu){
    for(int i = 0; i < 120; i++){
        alu.update();
    }
}


// 15 + 1 = 16
void testADD(){
    // 15 = 00001111
    std::array<Node, 8> a = {
        Node(true), Node(true), Node(true), Node(true),
        Node(false), Node(false), Node(false), Node(false)
    };

    // 1 = 00000001
    std::array<Node, 8> b = {
        Node(true), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    std::array<Node, 8> output = {
        Node(false), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    Node carry_in(false);
    Node carry_out(false);

    // 00 = ADD
    Node op0(false);
    Node op1(false);

    ALU8 alu(
        getPointers(a),
        getPointers(b),
        &carry_in,
        &op0,
        &op1,
        getPointers(output),
        &carry_out
    );

    settle(alu);

    // 16 = 00010000
    assert(output[0].getSignal() == false);
    assert(output[1].getSignal() == false);
    assert(output[2].getSignal() == false);
    assert(output[3].getSignal() == false);
    assert(output[4].getSignal() == true);
    assert(output[5].getSignal() == false);
    assert(output[6].getSignal() == false);
    assert(output[7].getSignal() == false);

    assert(carry_out.getSignal() == false);
}


// 255 + 1 = 0 with CarryOut = 1
void testADDOverflow(){
    std::array<Node, 8> a = {
        Node(true), Node(true), Node(true), Node(true),
        Node(true), Node(true), Node(true), Node(true)
    };

    std::array<Node, 8> b = {
        Node(true), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    std::array<Node, 8> output = {
        Node(true), Node(true), Node(true), Node(true),
        Node(true), Node(true), Node(true), Node(true)
    };

    Node carry_in(false);
    Node carry_out(false);

    Node op0(false);
    Node op1(false);

    ALU8 alu(
        getPointers(a),
        getPointers(b),
        &carry_in,
        &op0,
        &op1,
        getPointers(output),
        &carry_out
    );

    settle(alu);

    for(int i = 0; i < 8; i++){
        assert(output[i].getSignal() == false);
    }

    assert(carry_out.getSignal() == true);
}


// Bitwise AND
void testAND(){
    std::array<Node, 8> a = {
        Node(true), Node(true), Node(false), Node(false),
        Node(true), Node(true), Node(false), Node(false)
    };

    std::array<Node, 8> b = {
        Node(true), Node(false), Node(true), Node(false),
        Node(true), Node(false), Node(true), Node(false)
    };

    std::array<Node, 8> output = {
        Node(false), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    Node carry_in(false);
    Node carry_out(false);

    // 01 = AND
    Node op0(false);
    Node op1(true);

    ALU8 alu(
        getPointers(a),
        getPointers(b),
        &carry_in,
        &op0,
        &op1,
        getPointers(output),
        &carry_out
    );

    settle(alu);

    bool expected[8] = {
        true, false, false, false,
        true, false, false, false
    };

    for(int i = 0; i < 8; i++){
        assert(output[i].getSignal() == expected[i]);
    }
}


// Bitwise OR
void testOR(){
    std::array<Node, 8> a = {
        Node(true), Node(true), Node(false), Node(false),
        Node(true), Node(true), Node(false), Node(false)
    };

    std::array<Node, 8> b = {
        Node(true), Node(false), Node(true), Node(false),
        Node(true), Node(false), Node(true), Node(false)
    };

    std::array<Node, 8> output = {
        Node(false), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    Node carry_in(false);
    Node carry_out(false);

    // 10 = OR
    Node op0(true);
    Node op1(false);

    ALU8 alu(
        getPointers(a),
        getPointers(b),
        &carry_in,
        &op0,
        &op1,
        getPointers(output),
        &carry_out
    );

    settle(alu);

    bool expected[8] = {
        true, true, true, false,
        true, true, true, false
    };

    for(int i = 0; i < 8; i++){
        assert(output[i].getSignal() == expected[i]);
    }
}


// Bitwise XOR
void testXOR(){
    std::array<Node, 8> a = {
        Node(true), Node(true), Node(false), Node(false),
        Node(true), Node(true), Node(false), Node(false)
    };

    std::array<Node, 8> b = {
        Node(true), Node(false), Node(true), Node(false),
        Node(true), Node(false), Node(true), Node(false)
    };

    std::array<Node, 8> output = {
        Node(false), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    Node carry_in(false);
    Node carry_out(false);

    // 11 = XOR
    Node op0(true);
    Node op1(true);

    ALU8 alu(
        getPointers(a),
        getPointers(b),
        &carry_in,
        &op0,
        &op1,
        getPointers(output),
        &carry_out
    );

    settle(alu);

    bool expected[8] = {
        false, true, true, false,
        false, true, true, false
    };

    for(int i = 0; i < 8; i++){
        assert(output[i].getSignal() == expected[i]);
    }
}


int main(){

    testADD();
    testADDOverflow();

    testAND();
    testOR();
    testXOR();

    return 0;
}