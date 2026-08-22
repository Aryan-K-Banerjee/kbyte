#include "components/RippleCarryAdder8.h"
#include <array>
#include <cassert>


// Helper to get Node* arrays from Node arrays.
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


// Fully propagate through all 8 Full Adders.
void settle(RippleCarryAdder8& adder){
    for(int i = 0; i < 40; i++){
        adder.update();
    }
}


// 0 + 0 = 0
void testAddZero(){
    std::array<Node, 8> a = {
        Node(false), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    std::array<Node, 8> b = {
        Node(false), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    std::array<Node, 8> sum = {
        Node(true), Node(true), Node(true), Node(true),
        Node(true), Node(true), Node(true), Node(true)
    };

    Node carry_in(false);
    Node carry_out(true);

    RippleCarryAdder8 adder(
        getPointers(a),
        getPointers(b),
        &carry_in,
        getPointers(sum),
        &carry_out
    );

    settle(adder);

    for(int i = 0; i < 8; i++){
        assert(sum[i].getSignal() == false);
    }

    assert(carry_out.getSignal() == false);
}


// 1 + 1 = 2
void testOnePlusOne(){
    std::array<Node, 8> a = {
        Node(true), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    std::array<Node, 8> b = {
        Node(true), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    std::array<Node, 8> sum = {
        Node(false), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    Node carry_in(false);
    Node carry_out(false);

    RippleCarryAdder8 adder(
        getPointers(a),
        getPointers(b),
        &carry_in,
        getPointers(sum),
        &carry_out
    );

    settle(adder);

    // 00000010
    assert(sum[0].getSignal() == false);
    assert(sum[1].getSignal() == true);

    for(int i = 2; i < 8; i++){
        assert(sum[i].getSignal() == false);
    }

    assert(carry_out.getSignal() == false);
}


// 15 + 1 = 16
void testCarryRipple(){
    std::array<Node, 8> a = {
        Node(true), Node(true), Node(true), Node(true),
        Node(false), Node(false), Node(false), Node(false)
    };

    std::array<Node, 8> b = {
        Node(true), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    std::array<Node, 8> sum = {
        Node(false), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    Node carry_in(false);
    Node carry_out(false);

    RippleCarryAdder8 adder(
        getPointers(a),
        getPointers(b),
        &carry_in,
        getPointers(sum),
        &carry_out
    );

    settle(adder);

    // 00010000
    assert(sum[0].getSignal() == false);
    assert(sum[1].getSignal() == false);
    assert(sum[2].getSignal() == false);
    assert(sum[3].getSignal() == false);
    assert(sum[4].getSignal() == true);

    assert(sum[5].getSignal() == false);
    assert(sum[6].getSignal() == false);
    assert(sum[7].getSignal() == false);

    assert(carry_out.getSignal() == false);
}


// 255 + 1 = 256
void testOverflow(){
    std::array<Node, 8> a = {
        Node(true), Node(true), Node(true), Node(true),
        Node(true), Node(true), Node(true), Node(true)
    };

    std::array<Node, 8> b = {
        Node(true), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    std::array<Node, 8> sum = {
        Node(true), Node(true), Node(true), Node(true),
        Node(true), Node(true), Node(true), Node(true)
    };

    Node carry_in(false);
    Node carry_out(false);

    RippleCarryAdder8 adder(
        getPointers(a),
        getPointers(b),
        &carry_in,
        getPointers(sum),
        &carry_out
    );

    settle(adder);

    for(int i = 0; i < 8; i++){
        assert(sum[i].getSignal() == false);
    }

    assert(carry_out.getSignal() == true);
}


// 85 + 42 = 127
void testGeneralAddition(){
    // 85 = 01010101
    std::array<Node, 8> a = {
        Node(true),  Node(false), Node(true),  Node(false),
        Node(true),  Node(false), Node(true),  Node(false)
    };

    // 42 = 00101010
    std::array<Node, 8> b = {
        Node(false), Node(true),  Node(false), Node(true),
        Node(false), Node(true),  Node(false), Node(false)
    };

    std::array<Node, 8> sum = {
        Node(false), Node(false), Node(false), Node(false),
        Node(false), Node(false), Node(false), Node(false)
    };

    Node carry_in(false);
    Node carry_out(false);

    RippleCarryAdder8 adder(
        getPointers(a),
        getPointers(b),
        &carry_in,
        getPointers(sum),
        &carry_out
    );

    settle(adder);

    // 127 = 01111111
    assert(sum[0].getSignal() == true);
    assert(sum[1].getSignal() == true);
    assert(sum[2].getSignal() == true);
    assert(sum[3].getSignal() == true);
    assert(sum[4].getSignal() == true);
    assert(sum[5].getSignal() == true);
    assert(sum[6].getSignal() == true);
    assert(sum[7].getSignal() == false);

    assert(carry_out.getSignal() == false);
}


int main(){

    testAddZero();
    testOnePlusOne();
    testCarryRipple();
    testOverflow();
    testGeneralAddition();

    return 0;
}